/*
	忽略信号，press ctrl+c 不会对进程产生影响
		ctrl+z kill进程
*/
#include <stdio.h>
#include <signal.h>

int main()
{
	signal(SIGINT,SIG_IGN);

	while(1)
	{
		printf("haha\n");
		sleep(1);
	}
	return 0;
}
