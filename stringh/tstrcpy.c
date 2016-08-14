/*
strcpy 函数原型 char * strcpy(char * strDest,const char * strSrc); 

参考学习网址：http://blog.csdn.net/wconvey/article/details/21150103
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
char *address = strDest; return address
address 就是新的strDest的地址
是为了实现链式表达式 例如
 int length = strlen( strcpy( strDest, “hello world”) );
否则要分成两句写

不能返回 strSrc
返回strSrc的原始值是错误的，源字符串肯定是已知的
为了保护源字符串，形参用const限定strSrc所指的内容
把const char *作为char *返回，类型不符，编译报错

*/
char *m_strcpy(char * strDest, const char * strSrc)
{
	// assert 或者 判断后加上异常处理
	assert(strDest != NULL && strSrc != NULL);
	
	char *address = strDest;
	
        // 循环是先赋值，再判断是否为零，是会给strDest赋上strSrc中结尾'\0'的
	while((*strDest++ = *strSrc++) != '\0')
		NULL;

	return address;
}

int main()
{	
	char src[] = "abc";
	char dest[] = {'1','2','\0','3','4','\0'};
	int len = strlen(strcpy(src, dest));
	printf("len:%d,str:%s\n",len,src);

	char src2[] = "abc";
	char dest2[] = {'1','2','3','4','\0'};
	int len2 = strlen(strcpy(src2, dest2));
	printf("len:%d,str:%s\n",len2,src2);

	return 0;
}
