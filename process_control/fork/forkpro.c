/*
一共创建了三个进程
× fork的返回值不同
× 短路原则

main 进程中创建了一个子进程

子进程 将创建子进程
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	fork() || fork(); 
		
	printf("XX\n");
	exit(0);
}
