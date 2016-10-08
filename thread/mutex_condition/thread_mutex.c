#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 10
int cnt;
pthread_mutex_t mutex;

void* thread1(void* arg)
{
	pthread_mutex_lock(&mutex);
	if(cnt < MAX)
	{
		cnt++;
		printf("in thread 1:cnt=%d\n", cnt);
		sleep(1);
	}else{
		pthread_exit("exit");
	}
	pthread_mutex_unlock(&mutex);
	return arg;	
}

void* thread2(void* arg)
{
	pthread_mutex_lock(&mutex);
	if(cnt < MAX)
	{
		cnt ++;
		printf("in thread 2:cnt=%d\n", cnt);
		sleep(1);
	}else{
		pthread_exit("");
	}
	pthread_mutex_unlock(&mutex);

	return arg;	
}

int main()
{
	cnt = 0;
	pthread_t th1;
	pthread_t th2;
	pthread_mutex_init(&mutex, NULL);
	while(cnt < MAX){
		pthread_create(&th1, NULL, thread1, NULL);
		pthread_create(&th2, NULL, thread2, NULL);
	}
	pthread_join(th1,NULL);
	printf("thread1 exit\n");
	pthread_join(th2,NULL);
	printf("thread2 exit\n");
	pthread_mutex_destroy(&mutex);
	printf("in main:cnt=%d\n", cnt);
	return 0;
}
