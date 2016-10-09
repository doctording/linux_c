#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<sys/sem.h>
using namespace std;

// 联合体，用于semctl初始化
union semun {
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};


class semaphore {
private:
    int sem_id; //信号量ID，内核中创建
    int init_sem(int);
public:
    semaphore(const char*, int); /*构造函数*/
    ~semaphore();                /*析构函数*/
    void P();                    /*P操作*/
    void V();                    /*V操作*/
};
