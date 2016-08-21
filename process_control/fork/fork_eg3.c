/*
子进程 获得了父进程的数据空间，堆，栈的副本，
并不共享这些存储空间，他们共享正文段(代码段，只读的，放程序代码)

子进程 对变量的修改并不会影响父进程中该变量的值
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int globvar = 6; //全局初始化变量

int main()
{
	pid_t pid; //fpid表示fork函数返回的值
	
	int var = 88;

	pid = fork();
	if (pid < 0)
		printf("error in fork!\n");
	else if (pid == 0) {
		globvar++;
		var++;
	}
	else {
		sleep(2); 
	}  
	printf("globvar=%d,var=%d\n", globvar, var);
	exit(0);
}
