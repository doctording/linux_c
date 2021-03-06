信号概念
===

信号是软件中断，很比较重要的应用程序都需要处理信号。信号提供了一种处理异步事件的方法，
例如，中断用户键入中断键，则会通过信号机制停止一个程序，或及早终止管道中的下一个程序。


---

每一个信号都有一个名字。这些名字都是以SIG开头，
如SIGABRT是夭折信号，当进程调用abort函数时产生这种信号。SIGALRM是闹钟信号，当由alarm函数设置的计时器超时后产生此信号。

在头文件<signal.h>中，信号都会被定义成正整数。
内核包括对用户级别应用程序有意义的头文件，这被认为是一种糟糕的形式，所以如果应用程序和内核两者都需要使用同一种定义，那么就需要将有关信息放置在内核头文件中，然后再用户级头文件中再包括该内核头文件。
不存在编号为0的信号，kill函数都信号编号为0的特殊的应用。此种信号称为空信号。

信号是异步事件的一种经典实例。
产生信号的事件对进程而言是随机出现的，进程不能简单的测试一个变量如errno来判断是否出现一个信号，
而是必须告诉内核“在出现这种信号时应该执行下列操作”。

可以要求内核在某个信号出现时按照下列三种方式之一去处理，我们称之为信号的处理或者信号的相关的动作。

1、忽略此信号。大多数信号都可以使用这种信号，但是有两种信号不能忽略：SIGKILL和SIGSTOP，因为这两种信号向超级用户
提供了可以终止或者停止任何进程的可靠方法。另外，如果进程发生硬件异常的话，如果被忽略，进程的运行行为是不可预测的。

2、捕捉信号。为了做到这一点，要通知内核在某种信号发生时调用一个用户函数，在用户函数中，可执行用户希望对这种时间的处理。

3、执行默认操作。每一种信号系统都提供了默认的操作。注意，针对大多数信号的默认操作动作是终止进程。
需要注意：如果进程在处理一个信号返回前的时候有产生了一个信号，那么同等或高优先级的信号会中断低优先级的信号处理
