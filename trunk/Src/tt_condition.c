#include "../Inc/tt_thread.h"


/* Available in: irq, thread. */
void tt_cond_init (TT_COND_T *cond)
{
	if (cond == NULL)
		return;
	cond->locked_thread = NULL;
	cond->mutex			= NULL;
}


typedef struct
{
	TT_COND_T	*cond;
	TT_MUTEX_T	*mutex;
	bool		wait_on_recursive_mutex;
} __WAIT_T;

static void __tt_cond_wait (void *arg)
{
	__WAIT_T *wait_args	= (__WAIT_T *) arg;
	TT_COND_T	*cond	= wait_args->cond;
	TT_MUTEX_T	*mutex	= wait_args->mutex;
	TT_THREAD_T	*thread;

	/* Condition wait on this mutex */	
	cond->mutex						= mutex;
	cond->wait_on_recursive_mutex	= wait_args->wait_on_recursive_mutex;

	/* Unlock the mutex */
	__tt_mutex_unlock ((void *)mutex, mutex->locked_thread);

	/* Suspend current thread and put it onto the waiting list. */
	thread = tt_thread_self ();
	listDetach (&thread->list_schedule);
	thread->wait_parent = cond;

	if (cond->locked_thread != NULL)
	{
		/* Append "cond->locked_thread" to the right of "thread" */
		listAttach (&cond->locked_thread->list_schedule, &thread->list_schedule);
	}
	else
	{
		/* Head thread wait on this condition variable */
		cond->locked_thread = thread;
	}

	__tt_schedule ();
}


/* Available in: thread. */
void tt_cond_wait (TT_COND_T *cond, TT_MUTEX_T *mutex)
{
	__WAIT_T wait_args;
	wait_args.cond						= cond;
	wait_args.mutex						= mutex;
	wait_args.wait_on_recursive_mutex	= false;
	tt_syscall ((void *) &wait_args, __tt_cond_wait);
}


/* Wait cond on a recursive mutex */
void tt_cond_wait2 (TT_COND_T *cond, TT_RMUTEX_T *mutex)
{
	__WAIT_T	wait_args;
	int			lock_count;
	TT_THREAD_T	*thread;

	lock_count							= mutex->lock_count;
	thread								= mutex->thread;

	mutex->lock_count					= 0;
	mutex->thread						= NULL;

	wait_args.cond						= cond;
	wait_args.mutex						= &mutex->mutex;
	wait_args.wait_on_recursive_mutex	= true;
	tt_syscall ((void *) &wait_args, __tt_cond_wait);

	mutex->lock_count					= lock_count;
	mutex->thread						= thread;
}




typedef struct
{
	TT_COND_T	*cond;
	bool		wakeup_all;
	int			lock_count;
	TT_THREAD_T	*thread;
} __COND_ARG_T;

static void __tt_cond_signal (void *arg)
{
	__COND_ARG_T	*cond_args		= (__COND_ARG_T *)arg;
	TT_COND_T		*cond			= cond_args->cond;
	TT_MUTEX_T		*mutex			= cond->mutex;
	TT_THREAD_T		*owner_thread	= cond->mutex->owner_thread;
	if (owner_thread != NULL)
	{
		if (owner_thread!= tt_thread_self ())
		{
			/* Mutex has been locked by another thread,
			   it should be an error for user's application in this case, ignore it! */
			return;
		}
	}

	/* Wakeup locked_thread */
	while (cond->locked_thread != NULL)
	{
		/* Wake up a suspended thread. */
		TT_THREAD_T *thread = cond->locked_thread;
		
		/* Set new head thread */
		if (listIsEmpty (&thread->list_schedule) != false)
			cond->locked_thread = NULL;
		else
		{
			LIST_T *locked_thread = thread->list_schedule.pNext;
			cond->locked_thread = GetParentAddr (locked_thread, TT_THREAD_T, list_schedule);
		}

		/* set mutex lock on thread */
		__tt_mutex_lock (mutex, thread);		

		/* Append the thread to running thread */
		if (owner_thread != NULL)
		{
			__tt_mutex_unlock ((void *)mutex, thread);
			__tt_mutex_lock (mutex, owner_thread);
			if (cond->wait_on_recursive_mutex != false)
			{
				TT_RMUTEX_T *rmutex		= GetParentAddr (mutex, TT_RMUTEX_T, mutex);
				cond_args->lock_count	= rmutex->lock_count;
				cond_args->thread	= rmutex->thread;
			}
			owner_thread = NULL;
		}
		else
		{
			tt_set_thread_running (thread);
		}


		if (cond_args->wakeup_all == false)
		{
			break;
		}
	}
}


static void tt_cond_wakeup (TT_COND_T *cond, bool wakeup_all)
{
	__COND_ARG_T cond_args;
	cond_args.cond			= cond;
	cond_args.wakeup_all	= wakeup_all;
	cond_args.lock_count	= 0;
	//cond_args.thread		= NULL;

	tt_syscall ((void *) &cond_args, __tt_cond_signal);

	if (cond_args.lock_count != 0)
	{
		TT_RMUTEX_T *rmutex		= GetParentAddr (cond->mutex, TT_RMUTEX_T, mutex);
		rmutex->lock_count		= cond_args.lock_count;
		rmutex->thread			= cond_args.thread;
	}
}

/* Available in: irq, thread. */
void tt_cond_signal (TT_COND_T *cond)
{
	tt_cond_wakeup (cond, false);
}

/* Available in: irq, thread. */
void tt_cond_broadcast (TT_COND_T *cond)
{
	tt_cond_wakeup (cond, true);
}

