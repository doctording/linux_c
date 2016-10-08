/*
 * 条件变量的作用在于他给多个线程提供了一个汇合的场所
 × 
 * 线程1 等待gnum >=5 
 * 线程2 唤醒 线程 1
 × 之后 两个线程一起操作gnum++ 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int gnum = 1;

void* thread1(void* arg)
{
	for(;;)
	{
		printf("\nin thread 1\n");
		pthread_mutex_lock(&mutex);
		sleep(1);
		while(gnum < 5) {
			printf("thread1:I'm blocking,waiting for gum >= 5\n\n");
			pthread_cond_wait(&cond,&mutex);
			printf("thread2:I'm wake up\n\n");
		}
		// 当线程2调用pthread_cond_signal(&cond)时，线程1在这里重启
		gnum ++;
		printf("thead1 add one to gnum,now gnum=%d\n",gnum);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(0);
	return arg;	
}

void* thread2(void* arg)
{
	for(;;)
	{
		printf("\nin thread 2\n");
		pthread_mutex_lock(&mutex);
		sleep(1);
		// 临界资源
		// 当线程2调用pthread_cond_signal(&cond)时，线程1在这里重启
		gnum ++;
		printf("thead2 add one to gnum,now gnum=%d\n",gnum);
		if(gnum == 5) // 可以通知线程1 ,让线程1
			pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(0);
	return arg;	

}

int main()
{
	pthread_t th1;
	pthread_t th2;
	//pthread_mutex_init(&mutex, NULL);
	pthread_create(&th1, NULL, thread1, NULL);
	pthread_create(&th2, NULL, thread2, NULL);
	pthread_join(th1,NULL);
	printf("thread 1 exit\n");
	pthread_join(th2,NULL);
	printf("thread 2 exit\n");
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
