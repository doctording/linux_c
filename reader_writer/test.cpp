/*
 * 第一类读-写写者问题
 *
 * 读者优先，除非有写者在写文件，否则没有一个读者需要等待
 *
 */
#include<iostream>
#include<unistd.h>  // sleep
#include<pthread.h>
#include"semaphore.h"
	
using namespace std;

#define N 5
// http://blog.csdn.net/lwfcgz/article/details/8091242
int readcount = 0;
semaphore mutex("/", 1);           // 临界区互斥信号量
semaphore wri("/home", N);       // 写者

int i=0;
int j=0;

void* reader(void* arg)
{
	mutex.P();
	readcount = readcount + 1;
	if(readcount == 1)
	{
		wri.P();
	}
	mutex.V();
	//sleep(1);
	printf("reader id=%d is reading now\n",(int)arg);

	mutex.P();
	
	printf("reader id=%d is read over\n",(int)arg);
	readcount = readcount - 1;
	if(readcount == 0)
		wri.V();
	mutex.V();
	return arg;
}

void* writer(void* arg)
{	
	wri.P();
	//sleep(2);
	printf("                               \033[1;31m");
	printf("writer id=%d is now writting\n", (int)arg);
	wri.V();
	printf("                               writer id=%d over\n",(int)arg);
	printf("\033[0m");
	return arg;
}

int main()
{
	pthread_t id[10];
	int k;
	for(k=0; k<2; ++k)
		pthread_create(&id[k], NULL, reader, (void*)(k+1));
	
	pthread_t id2[5];
	for(int k=0; k<5; ++k)
		pthread_create(&id2[k], NULL, writer, (void*)(k+1));

	for(k=2; k<10; ++k)
		pthread_create(&id[k], NULL, reader, (void*)(k+1));

	sleep(2);
	return 0;
}
