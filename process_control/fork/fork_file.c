/*
父进程 和 子进程对打开文件的共享
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
 
int main()
{
        int fd;
        char c[3];
        /*打开文件foobar.txt，采用的是只读形式*/
        fd = open("foobar.txt",O_RDONLY,0);
 
        if(fork()==0)//子进程
        {
                read(fd,&c,2);/*读文件的一个字节到c中*/
                c[2]='\0';
                printf("c = %s\n",c);
                exit(0);
        /*子进程结束*/
        }
        /*下面是父进程的读操作*/
        wait(NULL);
        read(fd,&c,2);
        c[2]='\0';
        printf("c = %s\n",c);
        exit(0);
}
