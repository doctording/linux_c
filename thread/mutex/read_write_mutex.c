#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define Read_Num 2

pthread_rwlock_t lock;

typedef struct data {
	int I;
	float F;
}Data;

Data *pdata = NULL;

Data* createData(int i,int f)
{
	Data* d = (Data*)malloc(sizeof(Data));
	if(d == NULL)
		return NULL;

	d->F = f;
	d->I = i;
	return d;
}

void *readData(void * arg)
{
	int id = (int)arg;
	while(1)
	{
		pthread_rwlock_rdlock(&lock); // 读锁
		printf("reader %d is reading data!\n", id);
		if(pdata == NULL)
		{
			printf("data is NULL\n\n");
		}
		else
		{
			printf("data: I = %d, F = %f \n\n", pdata->I, pdata->F);
		}
		pthread_rwlock_unlock(&lock); // 释放锁
		
		sleep(1);
	}
	pthread_exit(0);
}

void *writeData()
{
	float a = 1.1;
	while(1)
	{
		pthread_rwlock_wrlock(&lock); // 写锁
		printf("writer is writing data!\n");
		if(pdata == NULL)
		{
			if(a > 10)
				a = 1.1;
			pdata = createData(1, a);
			a += 1.0;
			printf("Writer is writing data: %d, %f\n\n", pdata->I, pdata->F);
		}
		else
		{
			free(pdata);
			pdata = NULL;
			printf("writer free the data!\n\n");
		}
		pthread_rwlock_unlock(&lock); // 释放锁
			
		sleep(1);
	}
	pthread_exit(0);
}

int main()
{
	pthread_rwlock_init(&lock, NULL);  

	pthread_t reader[Read_Num];
	pthread_t writer;
	int i;
	for(i = 0;i<Read_Num;i++)
	{
		pthread_create(&reader[i],NULL,readData,(void *)i);
	}

	pthread_create(writer, NULL, writeData, NULL);

	for(i = 0;i<Read_Num;i++)
		pthread_join(reader[i], NULL);
	pthread_join(writer, NULL);

	pthread_rwlock_destroy(&lock);

	sleep(1);
	return 0;
}

