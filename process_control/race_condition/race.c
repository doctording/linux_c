#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void charactatime(char*);

int main(void)
{
	pid_t pc;
	pc = fork();
	if(pc < 0)
		printf("Error occured on forking.\n");
	else if(pc == 0){
		charactatime("output from child\n");
	}else{
		charactatime("output from parent\n");
	}

	return 0;
}


static void charactatime(char* str)
{
	char *ptr;
	int c;
	setbuf(stdout, NULL); // 关闭缓冲
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}
