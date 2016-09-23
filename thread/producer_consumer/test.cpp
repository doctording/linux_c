#include<iostream>
#include<unistd.h>  // sleep
#include<pthread.h>
#include"semaphore.h"

using namespace std;

#define N 5

semaphore mutex("/", 1);           // 临界区互斥信号量
semaphore empty("/home", N);       // 记录空缓冲区数，初值为N
semaphore full("/home/john",0); // 记录满缓冲区数，初值为0
int buffer[N];                     // 缓冲区，大小为N
int i=0;
int j=0;

void* producer(void* arg)
{
    empty.P();                 // empty减1
    mutex.P();

    buffer[i] = 10 + rand() % 90;
    printf("Producer %d write Buffer[%d]: %d\n",(int)arg,i+1,buffer[i]);
    i = (i+1) % N;

    mutex.V();
    full.V();                  // full加1 
    return arg;
}

void* consumer(void* arg)
{
    full.P();                  // full减1
    mutex.P();

    printf("                               \033[1;31m");
    printf("Consumer %d read Buffer[%d]: %d\n",(int)arg,j+1,buffer[j]);
    printf("\033[0m");
    j = (j+1) % N;

    mutex.V();
    empty.V();                 // empty加1
    return arg;
}

int main()
{
    pthread_t id[10];

    // 开10个生产者线程，10个消费者线程
    for(int k=0; k<10; ++k)
        pthread_create(&id[k], NULL, producer, (void*)(k+1));

    for(int k=0; k<10; ++k)
        pthread_create(&id[k], NULL, consumer, (void*)(k+1));

    sleep(1);
    return 0;
}
