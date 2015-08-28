This project has been moved to --
https://github.com/xhawk18/TinyThread

TinyThread is a small multi-thread library for embedded system.<br>
Currently it supports Cortex-M0 chips, such as Nuvoton NUC100 and M051 series.<br>
<hr />
<h3>TinyThread Specifications</h3>
<ul><li>Multitask<br>
<ul><li>Round-Robin<br>
</li><li>Preemptive<br>
</li><li>Can avoid priority inversion by mutex<br>
</li></ul></li><li>Task Specifications<br>
<ul><li>Define Tasks, Unlimited<br>
</li><li>Active Tasks, Unlimited<br>
</li><li>User Priorities, Unlimited<br>
</li><li>Thread Stack Checking, Supported<br>
</li><li>Context Switch Time,<br>
<ul><li><300 cycles without thread sleeping and stack checking supported.<br>
</li><li><400 cycles with thread sleeping and stack checking supported.<br>
</li></ul></li></ul></li><li>Time<br>
<ul><li>delay, supported by tt_sleep()<br>
</li><li>micro delay, supported by tt_usleep()<br>
</li></ul></li><li>Inter-Task Communication<br>
<ul><li>Semaphores, Unlimited<br>
</li><li>Mutexes, Unlimited<br>
</li><li>Recursive mutexes, Unlimited<br>
</li><li>Conditions, Unlimited<br>
</li><li>Mailbox(Message), Unlimited<br>
</li></ul></li><li>Thread/Irq Communication<br>
<ul><li>Semaphores/Mutexes/Recursive Mutexed/Conditions can be used in Irq. (Some functions are limited, see Doc\TinyThread.doc)</li></ul></li></ul>

<h3>Memory specifications</h3>
<ul><li>RAM Space for a Task<br>
<ul><li>Task Stack Size + 68 Bytes(MAX)<br>
</li><li>Task Stack Size + 28 Bytes(MIN)<br>
</li></ul></li><li>RAM Space for a Semaphore, 8 Bytes<br>
</li><li>RAM Space for a Mutex, 8 Bytes<br>
</li><li>RAM Space for a Recursive Mutex, 16 Bytes<br>
</li><li>RAM Space for a Condition, 12 Bytes<br>
</li><li>RAM Space for a Mailbox, 40 Bytes + user defined message buffer</li></ul>

<h3>Reference document</h3>
<ul><li>Doc\TinyThread.doc</li></ul>

<h3>About the BSP</h3>
<ul><li>This library contains part of NUC100 and M051 series BSP.<br>
<blockquote>To get full BSP libraries, please visit<br>
<blockquote><a href='http://www.nuvoton.com/NuMicro'>http://www.nuvoton.com/NuMicro</a></blockquote></blockquote></li></ul>
