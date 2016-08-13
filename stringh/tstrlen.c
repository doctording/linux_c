/*
 strlen 函数原型 size_t strlen(const char *str);
	读取非NULL的 const char*
	读取每个字节，当读取到的内容是\0时 停止
	返回size_t 或 unsigned int 

	源码实现中采用了字节对其，字节读取，地址相减等高效做法
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str1 = "123"; // “123”在静态区，是常量 只读，后面自动加了个\0
	char str2[] = {'1', '2', '3'};//str2在栈上，但是3后面的内容不确定，所以strlen不去确定
	char str3[] = {'1', '2', '\0', '3', '4'};
	// str4 str5 后面都会自动加上\0,与str1类似
	char str4[5] = "123";
	char str5[5] = "12345";

	printf("strlen(str1)=%d, sizeof(str1)=%d\n", strlen(str1), sizeof(str1));
	printf("strlen(str2)=%d, sizeof(str2)=%d\n", strlen(str2), sizeof(str2));
	printf("strlen(str3)=%d, sizeof(str3)=%d\n", strlen(str3), sizeof(str3));
	printf("strlen(str4)=%d, sizeof(str4)=%d\n", strlen(str4), sizeof(str4));
	printf("strlen(str5)=%d, sizeof(str5)=%d\n", strlen(str5), sizeof(str5));
	
	int a = 0x12345678;
	int *pa = &a;
	printf("strlen(pa)=%d, sizeof(pa)=%d\n", strlen((const char*)pa), sizeof(pa));

	int b = 0x12340078; //注意测试下自己机器的大小端
	int *pb = &b;
	printf("strlen(pb)=%d, sizeof(pb)=%d\n", strlen((const char*)pb), sizeof(pb));

	return 0;
}
