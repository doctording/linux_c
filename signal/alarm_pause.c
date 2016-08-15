/*
	#include <unistd.h>
	unsigned int alarm(unsigned int seconds);
	使用alarm函数可以设置一个定时器（闹钟），在将来的某个时刻
 	该定时器会超时，当定时器超时时，产生SIGALRM信号。如果忽略或者
	捕捉该信号，则其默认动作是终止调用该alarm函数的进程。
	
	#include <unistd.h>
	int pause(void);
	pause函数使调用进程挂起，直到捕捉到一个信号，只有执行了一个信号
	处理程序并从其返回时，pause才返回，在这种情况下，pause返回-1
*/
#include <unistd.h>  
#include <sys/types.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <signal.h>  
  
int main()  
{  
	void wakeup(int);
  	signal(SIGALRM, wakeup); // catch it
	printf("alarm is set\n");
	alarm(4); //set clock
	pause();// pause
	printf("morning so soon?\n"); // back to work
	exit(0);  
}

void wakeup(int signum)
{
#ifndef SHHHH
	printf("Alarm received from kernel\n");
#endif
}
