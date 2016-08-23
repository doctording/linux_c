#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAXNUM      100
#define OPEN_DEV    "/dev/input/mice"

int max2(int a, int b)
{
    return a>b?a:b;
}


int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval, fd;
    char buf[MAXNUM];

    fd = open(OPEN_DEV, O_RDONLY);//打开鼠标设备
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);//输入
        FD_SET(fd, &rfds);//鼠标设备
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        retval = select(max2(0,fd)+1, &rfds, NULL, NULL, &tv);
        if (retval < 0) // 返回-1 出错
            printf ("error\n");
        if (retval == 0) // 返回0 超时
            printf ("No data within 5 seconds\n");
        if (retval > 0) { // 大于0 为描述符的数目
            if (FD_ISSET(0, &rfds)) { //判断输入描述符是否可用
                printf ("Data is available from keyboard now\n");
                read(0, buf, MAXNUM);
            }
            if (FD_ISSET(fd, &rfds)) { //判断鼠标设备描述符是否可用
                printf ("Data is available from mouse now\n");
                read(fd, buf, MAXNUM);
            }
        }
    }
    return 0;
}
