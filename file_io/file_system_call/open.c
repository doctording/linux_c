/*

如果当前目录下以存在test.txt，屏幕上就会打印“open error”；不存在则创建该文件，并打印“open success”
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_PATH   "./test.txt"

int main(void)
{
    int fd;
    if ((fd = open(FILE_PATH, O_RDWR | O_CREAT | O_EXCL, 0666)) < 0) {
        printf("open error\n");
        exit(-1);
    } else {
        printf("open success\n");
    }
    return 0;
}
