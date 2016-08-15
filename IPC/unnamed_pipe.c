#include <stdio.h>
#include<string.h>
#include <unistd.h>

int main()
{
int p[2];
        int pid;
        char *str = "HelloWorld";
        char buf[128];
        memset(buf,'\0',128);

        if(pipe(p) == -1)
        {
                printf("function pipe() calls failed.");
                return -1;
        }

        if((pid=fork()) == -1)  //创建一个子进程
        {
                printf("function fork() calls failed.\n");
                return -1;
        }
        else if(pid == 0)  //在子进程中
        {
                printf("In sub : pid=%d\n",getpid());
                close(p[0]); //关闭读
		write(p[1],str,strlen(str)); //向无名管道中写入str
        }else {  //在父进程中
                printf("In father : pid=%d\n",getpid());
		close(p[1]); // 关闭写
                read(p[0],buf,strlen(str));  //读取无名管道
                printf("In father : buf=%s\n",buf);
        }
}
