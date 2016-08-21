/*
当父进程忘了用wait()函数等待已终止的子进程时,子进程就会进入一种无父进程清理自己尸体的状态,此时的子进程就是僵尸进程.
*/
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
		sleep(20);
		printf("This is partent with pid of %d\n",getpid());
	}
	exit(0);
}
