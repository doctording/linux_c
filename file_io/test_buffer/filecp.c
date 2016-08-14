/*
测试 文件复制(linux cp命令) 不同的文件缓冲大小所用的时间
main 执行是 要传入 srcfile,destfile,buffersize
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

unsigned int BUFFERSIZE = 4096;

#define COPYMODE 0644

void oops(char *, char *);	//出错信息处理

int main(int ac, char *av[])
{
	if(ac != 4){
		fprintf(stderr,"usage:%s soource destination\n",*av);
		exit(1);
	}
	BUFFERSIZE = atoi(av[3]);

	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];
		
		
	if( (in_fd = open(av[1],O_RDONLY)) == -1)
		oops("Cannot open ",av[1]);

	if( (out_fd = creat(av[2],COPYMODE)) == -1)
		oops("Cannot create ",av[2]);

	clock_t start, finish;  
	double duration;  
	start = clock(); 
	
	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) // 复制文件
	{
		if(write(out_fd, buf, n_chars) != n_chars)
			oops("Write error to ", av[2]);
	}
	if( n_chars == -1)
		oops("Read error from ", av[1]);
	
	if( close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC; // 获得运行时间
	printf( "%f seconds\n", duration );  

	return 0;
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}
