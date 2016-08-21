#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid; //fpid表示fork函数返回的值
	int count=0;
	printf("fork!\n");
	pid = fork();
	if (pid < 0)
		printf("error in fork!\n");
	else if (pid == 0) {
		printf("i am the child process, my process id is %d\n",getpid());
		count++;
		printf("count=%d\n",count);
	}
	else {
		printf("i am the parent process, my process id is %d\n",getpid());
		count++;
		printf("count=%d\n",count);
	}  
	exit(0);
}
