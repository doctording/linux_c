/*
  程序调用signal后进入一个循环。
  如果进程接受到SIGINT信号，内核就调用f来处理这个信号
  程序跳转到那个函数，执行它的代码，然后返回到跳转前的位置，就行子过程调用一样
  例如 本例按下 ctrl+c是 f可以捕捉到信号，但之后可能接着执行main函数


  /usr/include/signal.h
  result = signal(int signum, void(*action)(int));

  signum 需响应的信号
  action 如何响应
  返回值 -1 遇到错误
         prevaction 成功返还
*/
#include <stdio.h>
#include <signal.h>

int main()
{
	void f(int); // declare the handle
	int i;
	signal(SIGINT,f); // install the handle

	for(i=0;i<5;i++)
	{
		printf("hello\n");
		sleep(1);
	}
	return 0;
}

void f(int signum)
{
	printf("OUCH!\n");
}
