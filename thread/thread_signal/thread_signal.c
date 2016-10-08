/*
 × 多个线程都注册了相同的信号，那么只有最后一次注册的有效
 × 
 */
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
 
static pthread_t g_thread_ids[2]={0};
 
void ouch1(int sig)
{
    printf("mainthread interrupted,thread id:%u\n",(unsigned int)pthread_self());
    //signal(SIGINT,SIG_DFL);
}
void ouch2(int sig)
{
    printf("child thread 1 interrupted,thread id:%u\n",(unsigned int)pthread_self());
    //signal(SIGINT,SIG_DFL);
}
void ouch3(int sig)
{
    printf("child thread 2 interrupted,thread id:%u\n",(unsigned int)pthread_self());
   //signal(SIGINT,SIG_DFL);
}
 
void thread_loop1(char* msg)
{ 
 
    printf("child thread 1 signal now \n");
    signal(SIGINT,ouch2); // 中断信号，ouch2处理函数
    printf("chilid thread1:%d,%s",(int)getpid(),msg);
    while(1);
   
}
void thread_loop2(char* msg)
{
    
    printf("child thread 2 signal now\n");
    signal(SIGINT,ouch3);
    printf("child thread2:%d,%s",(int)getpid(),msg);
    while(1);
}

void thread_wait2()
{
    //waiting for thread terminate
    if(g_thread_ids[0]!=0)
    {
        pthread_join(g_thread_ids[0],NULL);
        printf("thread %d terminated\n",getpid());
    }
    if(g_thread_ids[1]!=0)
    {
        pthread_join(g_thread_ids[1],NULL);
        printf("thread %d terminated\n",getpid());
    }
}
 
//=============test multi-thread test.
 
void start_test()
{
    pthread_t thread1,thread2;
    char *msg1="this is thread 1\n";
    char *msg2="this is thread 2\n";
    //printf("main thread signal now\n");
    signal(SIGINT,ouch1);// 主线程注册一个信号
    printf("main thread signal now\n");
    pthread_create(&thread1,NULL,(void*)thread_loop1,(void*)msg1);
    g_thread_ids[0]=thread1;
    pthread_create(&thread2,NULL,(void*)thread_loop2,(void*)msg2);
    g_thread_ids[1]=thread2;
 
    thread_wait2();
    printf("all thread finished its tasks\n");
 
    return ;
}
 
int main()
{   
    start_test();
    return 0;
}
