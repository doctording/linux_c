#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int fd;
    char buf[100];
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(-1);
    }
    read(fd, buf, 1);//读一个字节
    write(STDOUT_FILENO, buf, 1);//写到屏幕
    lseek(fd, 2, SEEK_CUR);

    read(fd, buf, 1);
    write(STDOUT_FILENO, buf, 1);
    lseek(fd, -2, SEEK_END);//文件倒数前2个字节

    read(fd, buf, 1);
    write(STDOUT_FILENO, buf, 1);
    lseek(fd, 1, SEEK_SET);//距离开始处1个字节

    read(fd, buf, 1);
    write(STDOUT_FILENO, buf, 1);
    close(fd);
    printf("\n");

    return 0;
}
