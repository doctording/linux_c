/*
	低地址存储低字节为小端
	          高      大
*/
#include <stdio.h>

int main()
{
	int a = 1;
	char *p = (char*)&a;
	if(*p == 1)
		printf("it's little endian\n");
	else
		printf("it's big endian\n");

	return 0;
}
