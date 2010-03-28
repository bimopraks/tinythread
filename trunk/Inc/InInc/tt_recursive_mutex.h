#ifndef INC__TT_RECURSIVE_MUTEX_H__
#define INC__TT_RECURSIVE_MUTEX_H__


typedef struct
{
	TT_MUTEX_T mutex;
	int lock_count;
	TT_THREAD_T *thread;
} TT_RMUTEX_T;	/* Recursive lock */


void tt_rmutex_init (TT_RMUTEX_T *rmutex);
void tt_rmutex_lock (TT_RMUTEX_T *rmutex);
int tt_rmutex_try_lock (TT_RMUTEX_T *rmutex);
int tt_rmutex_can_lock (TT_RMUTEX_T *rmutex);
void tt_rmutex_unlock (TT_RMUTEX_T *rmutex);

#endif
