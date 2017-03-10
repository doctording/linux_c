#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  

void* thread1( void *arg )  
{  
    printf( "thread 1 exiting\n");  
    return ((void *)1);  
}  

void* thread2( void *arg )  
{  
    printf( "thread 2 exiting\n");  
    pthread_exit((void *)2);  
}

int main( int argc, char *argv[] )  
{  
    	pthread_t tid1, tid2;  
    	void *tret;
	int ret;
	

   	ret = pthread_create(&tid1, NULL, thread1, NULL); //创建线程，并传递参数 
	if( ret != 0 ) {  
        	printf( "Create thread 1 error!\n");  
    	}
   	ret = pthread_create(&tid2, NULL, thread2, NULL); //创建线程，并传递参数 
	if( ret != 0 ) {  
        	printf( "Create thread 2 error!\n");  
    	}
        printf( "This is the main process.\n" );  
   
 	ret = pthread_join(tid1, &tret); // 以阻塞的方式等待thread指定的线程结束 线程间同步的操作
    	if(ret != 0)
	{
		printf("cannot join thread 1\n");
		exit(0);
	}
	printf("thread 1 exit code %ld\n", (long)tret);

 	ret = pthread_join(tid2, &tret); // 以阻塞的方式等待thread指定的线程结束 线程间同步的操作
    	if(ret != 0)
	{
		printf("cannot join thread 2\n");
		exit(0);
	}
	printf("thread 2 exit code %ld\n", (long)tret);

	exit(0);
}  
