wait函数的原型为:pid_t wait(int *status)
当进程退出时,它向父进程发送一个SIGCHLD信号,默认情况下总是忽略SIGCHLD信号,此时进程状态一直保留在内存中,直到父进程使用wait函数收集状态信息,才会清空这些信息.

用wait来等待一个子进程终止运行称为回收进程.
当父进程忘了用wait()函数等待已终止的子进程时,子进程就会进入一种无父进程的状态,此时子进程就是僵尸进程.
wait()要与fork()配套出现,如果在使用fork()之前调用wait(),wait()的返回值则为-1,正常情况下wait()的返回值为子进程的PID.
如果先终止父进程,子进程将继续正常进行，只是它将由init进程(PID 1)继承,当子进程终止时,init进程捕获这个状态.

---

wait（等待子进程中断或结束）
===
表头文件
#include<sys/types.h>
#include<sys/wait.h>

定义函数
pid_t wait(int * status);

函数说明
wait()会暂时停止目前进程的执行，直到有信号来到或子进程结束。
如果在调用wait()时子进程已经结束，则wait()会立即返回子进程结束状态值。子进程的结束状态值会由参数status 返回，而子进程的进程识别码也会一快返回。
如果不在意结束状态值，则参数status可以设成NULL。子进程的结束状态值请参考waitpid()。

返回值
如果执行成功则返回子进程识别码(PID)，如果有错误发生则返回-1。失败原因存于errno中。


waitpid - 等待子进程中断或结束
=====
表头文件
#include<sys/types.h>
#include<sys/wait.h>

定义函数
pid_t waitpid(pid_t pid,int * status,int options);

函数说明
waitpid()会暂时停止目前进程的执行，直到有信号来到或子进程结束。
如果在调用wait()时子进程已经结束，则wait()会立即返回子进程结束状态值。
子进程的结束状态值会由参数status返回，而子进程的进程识别码也会一快返回。
如果不在意结束状态值，则参数status可以设成NULL。

参数pid为欲等待的子进程识别码，其他数值意义如下:
pid<-1 等待进程组识别码为pid绝对值的任何子进程。
pid=-1 等待任何子进程，相当于wait()。
pid=0 等待进程组识别码与目前进程相同的任何子进程。
pid>0 等待任何子进程识别码为pid的子进程。

参数option可以为0 或下面的OR 组合
WNOHANG 如果没有任何已经结束的子进程则马上返回，不予以等待。
WUNTRACED 如果子进程进入暂停执行情况则马上返回，但结束状态不予以理会。
子进程的结束状态返回后存于status，底下有几个宏可判别结束情况
WIFEXITED(status)如果子进程正常结束则为非0值。
WEXITSTATUS(status)取得子进程exit()返回的结束代码，一般会先用WIFEXITED 来判断是否正常结束才能使用此宏。
WIFSIGNALED(status)如果子进程是因为信号而结束则此宏值为真
WTERMSIG(status)取得子进程因信号而中止的信号代码，一般会先用WIFSIGNALED 来判断后才使用此宏。
WIFSTOPPED(status)如果子进程处于暂停执行情况则此宏值为真。一般只有使用WUNTRACED 时才会有此情况。
WSTOPSIG(status)取得引发子进程暂停的信号代码，一般会先用WIFSTOPPED 来判断后才使用此宏。

返回值
如果执行成功则返回子进程识别码(PID)，如果有错误发生则返回-1。失败原因存于errno中。

