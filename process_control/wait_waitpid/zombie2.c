#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	pid_t pc,pr;
	pc = fork();
	if (pc < 0)
		printf("error ocurred!\n");
	else if(pc == 0){
		printf("This is child process with pid of %d\n",getpid());
	}
	else{
		wait(NULL); //回收子进程
		sleep(20);
		printf("This is partent with pid of %d\n",getpid());
	}
	exit(0);
}
