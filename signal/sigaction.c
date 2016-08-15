#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void show_handler(int sig)
{
    printf("I got signal %d\n", sig);
    int i;
    for(i = 0; i < 5; i++) {
        printf("i = %d\n", i);
        sleep(1);
    }
}

int main(void)
{
    int i = 0;
    struct sigaction act, oldact;
    act.sa_handler = show_handler;
    sigaddset(&act.sa_mask, SIGQUIT); // add sigquit to list(sa_mask) (1)
    act.sa_flags = SA_RESETHAND | SA_NODEFER;

    sigaction(SIGINT, &act, &oldact);
    while(1) {
        sleep(1);
        printf("sleeping %d\n", i);
        i++;
    }
}
/*
（1）如果在信号SIGINT(Ctrl + c)的信号处理函数show_handler执行过程中，本进程收到信号SIGQUIT(Crt+\)，将阻塞该信号，直到show_handler执行结束才会处理信号SIGQUIT。

运行实例
john@ubuntu:~/git_workspace/clib/signal$ ./sigaction.exe 
sleeping 0
sleeping 1
^CI got signal 2
i = 0
i = 1
i = 2
^Zi = 3
i = 4

[1]+  Stopped                 ./sigaction.exe
*/
