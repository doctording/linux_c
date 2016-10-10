/*
http://www.jb51.net/article/54827.htm
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  //linux环境中多线程的头文件，非C语言标准库，编译时最后要加 -lpthread 调用动态链接库
 
//工作链表的结构
typedef struct worker {
  void *(*process)(void *arg);  //工作函数
  void *arg;           //函数的参数
  struct worker *next;
}CThread_worker;
 
//线程池的结构
typedef struct {
  pthread_mutex_t queue_lock;   //互斥锁
  pthread_cond_t queue_ready;  //条件变量/信号量
 
  CThread_worker *queue_head;   //指向工作链表的头结点，临界区
  int cur_queue_size;       //记录链表中工作的数量，临界区
 
  int max_thread_num;       //最大线程数
  pthread_t *threadid;      //线程ID
 
  int shutdown;          //开关
}CThread_pool;
 
static CThread_pool *pool = NULL;  //一个线程池变量
int pool_add_worker(void *(*process)(void *arg), void *arg);  //负责向工作链表中添加工作
void *thread_routine(void *arg);  //线程例程
 
//线程池初始化
void pool_init(int max_thread_num)
{
  int i = 0;
 
  pool = (CThread_pool *) malloc (sizeof(CThread_pool));  //创建线程池
 
  pthread_mutex_init(&(pool->queue_lock), NULL);   //互斥锁初始化，参数为锁的地址
  pthread_cond_init( &(pool->queue_ready), NULL);   //条件变量初始化，参数为变量地址
 
  pool->queue_head = NULL;
  pool->cur_queue_size = 0;
 
  pool->max_thread_num = max_thread_num;
  pool->threadid = (pthread_t *) malloc(max_thread_num * sizeof(pthread_t));
  for (i = 0; i < max_thread_num; i++) {
    pthread_create(&(pool->threadid[i]), NULL, thread_routine, NULL); //创建线程, 参数为线程ID变量地址、属性、例程、参数
  }
 
  pool->shutdown = 0;
}
 
//例程，调用具体的工作函数
void *thread_routine(void *arg)
{
  printf("starting thread 0x%x\n", (int)pthread_self());
  while(1) {
    pthread_mutex_lock(&(pool->queue_lock));  //从工作链表中取工作，要先加互斥锁，参数为锁地址
 
    while(pool->cur_queue_size == 0 && !pool->shutdown) {    //链表为空
      printf("thread 0x%x is waiting\n", (int)pthread_self());
      pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));  //等待资源，信号量用于通知。会释放第二个参数的锁，以供添加；函数返回时重新加锁。
    }
 
    if(pool->shutdown) {
      pthread_mutex_unlock(&(pool->queue_lock));     //结束开关开启，释放锁并退出线程
      printf("thread 0x%x will exit\n", (int)pthread_self());
      pthread_exit(NULL);   //参数为void *
    }
 
    printf("thread 0x%x is starting to work\n", (int)pthread_self());
 
    --pool->cur_queue_size;
    CThread_worker *worker = pool->queue_head;
    pool->queue_head = worker->next;
 
    pthread_mutex_unlock (&(pool->queue_lock));   //获取一个工作后释放锁
    (*(worker->process))(worker->arg);   //做工作
    free(worker);
    worker = NULL;
  }
  pthread_exit(NULL);
}
 
//销毁线程池
int pool_destroy()
{
  if(pool->shutdown)   //检测结束开关是否开启，若开启，则所有线程会自动退出
    return -1;
  pool->shutdown = 1;
 
  pthread_cond_broadcast( &(pool->queue_ready) );   //广播，唤醒所有线程，准备退出
 
  int i;
  for(i = 0; i < pool->max_thread_num; ++i)
    pthread_join(pool->threadid[i], NULL);   //主线程等待所有线程退出，只有join第一个参数不是指针，第二个参数类型是void **，接收exit的返回值，需要强制转换
  free(pool->threadid);
  CThread_worker *head = NULL;
  while(pool->queue_head != NULL) {      //释放未执行的工作链表剩余结点
    head = pool->queue_head;
    pool->queue_head = pool->queue_head->next;
    free(head);
  }
 
  pthread_mutex_destroy(&(pool->queue_lock));   //销毁锁和条件变量
  pthread_cond_destroy(&(pool->queue_ready));
 
  free(pool);
  pool=NULL;
  return 0;
}
 
void *myprocess(void *arg)
{
  printf("threadid is 0x%x, working on task %d\n", (int)pthread_self(), *(int*)arg);
  sleep (1);
  return NULL;
}
 
//添加工作
int pool_add_worker(void *(*process)(void *arg), void *arg)
{
  CThread_worker *newworker = (CThread_worker *) malloc(sizeof(CThread_worker));
  newworker->process = process;  //具体的工作函数
  newworker->arg = arg;
  newworker->next = NULL;
 
  pthread_mutex_lock( &(pool->queue_lock) );   //加锁
 
  CThread_worker *member = pool->queue_head;   //插入链表尾部
  if( member != NULL ) {
    while( member->next != NULL )
      member = member->next;
    member->next = newworker;
  }
  else {
    pool->queue_head = newworker;
  }
  ++pool->cur_queue_size;
 
  pthread_mutex_unlock( &(pool->queue_lock) );  //解锁
 
  pthread_cond_signal( &(pool->queue_ready) );  //通知一个等待的线程
  return 0;
}
 
int main(int argc, char **argv)
{
  pool_init(3);  //主线程创建线程池，3个线程
 
  int *workingnum = (int *) malloc(sizeof(int) * 10);
  int i;
  for(i = 0; i < 10; ++i) {
    workingnum[i] = i;
    pool_add_worker(myprocess, &workingnum[i]);   //主线程负责添加工作，10个工作
  }
 
  sleep (5);
  pool_destroy();   //销毁线程池
  free (workingnum);
 
  return 0;
}
