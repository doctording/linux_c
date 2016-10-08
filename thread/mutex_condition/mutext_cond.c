#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int i =1;

void* thread1(void* arg)
{
	for(i = 1; i < MAX; i++)	
	{
		pthread_mutex_lock(&mutex);
		printf("thread1:i=%d\n",i);
		if(i % 3 == 0) {
			printf("thread1: I will notify thread2\n");
			pthread_cond_signal(&cond);
			printf("thread1: I'will sleep then release mutex\n");
			sleep(1);
		}
		pthread_mutex_unlock(&mutex);
		printf("--\n");
		sleep(1);
	}
	return arg;	
}

void* thread2(void* arg)
{
	while(i < MAX)
	{
		pthread_mutex_lock(&mutex);
		printf("thread2:i=%d\n",i);
		if(i % 3 != 0) {
			pthread_cond_wait(&cond,&mutex);
			printf("thread2:I am now waiting cond,and will sleep then ealse mutex\n");
			sleep(1);
		}
		pthread_mutex_unlock(&mutex);
		printf("--\n");
		sleep(1);
	}
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
