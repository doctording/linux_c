/*
pid_t waitpid(pid_t pid,int *status,int options)

waitpid的参数说明:

参数pid的值有以下几种类型:

pid>0时,只等待进程ID等于pid的子进程,不管其它已经有多少子进程运行结束退出了,只要指定的子进程还没有结束,waitpid就会一直等下去.

pid=-1时,等待任何一个子进程退出,没有任何限制,此时waitpid和wait的作用一模一样.

pid=0时,等待同一个进程组中的任何子进程,如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬.

pid<-1时,等待一个指定进程组中的任何子进程,这个进程组的ID等于pid的绝对值.

参数options的值有以下几种类型:

如果使用了WNOHANG参数,即使没有子进程退出,它也会立即返回,不会像wait那样永远等下去.

如果使用了WUNTRACED参数,则子进程进入暂停则马上返回,但结束状态不予以理会.

Linux中只支持WNOHANG和WUNTRACED两个选项,这是两个常数,可以用"|"运算符把它们连接起来使用，比如：

ret=waitpid(-1,NULL,WNOHANG | WUNTRACED);

如果我们不想使用它们,也可以把options设为0,如:ret=waitpid(-1,NULL,0);

waitpid的返回值比wait稍微复杂一些，一共有3种情况：
3)waitpid的返回值:

当正常返回的时候waitpid返回收集到的子进程的进程ID；

如果设置了选项WNOHANG,而调用中waitpid发现没有已退出的子进程可收集,则返回0；

如果调用中出错,则返回-1,这时errno会被设置成相应的值以指示错误所在；

当pid所指示的子进程不存在,或此进程存在,但不是调用进程的子进程,waitpid就会出错返回,这时errno被设置为ECHILD.
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pc, pr;
	pc = fork();
	if(pc < 0)
		printf("Error occured on forking.\n");
	else if(pc == 0){
		sleep(10);
		return 0;
	}

	do{
		pr = waitpid(pc, NULL, WNOHANG); //
		if(pr == 0){
			printf("No child exited\n");
			sleep(1);
		}
	}while(pr == 0);

	if(pr == pc)
		printf("successfully get child %d\n", pr);
	else
		printf("some error occured\n");

	return 0;
}
