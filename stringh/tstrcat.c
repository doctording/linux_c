/*

//将源字符串加const，表明其为输入参数, 注意返回值
char* strcat(char* strDest , const char* strSrc)
{
    //后文return address，故不能放在assert断言之后声明address
    char* address=strDest;
    assert( (strDest!=NULL)&&(strSrc!=NULL) );//对源地址和目的地址加非0断言
    while(*strDest)//是while(*strDest!=’\0’)的简化形式
    {
        //若使用while(*strDest++)，则会出错，因为循环结束后strDest还会执行一次++,
        //那么strDest将指向'\0'的下一个位置。/所以要在循环体内++；因为要使*strDest最后指
        //向该字符串的结束标志’\0’。
        strDest++;
    }
 
    while(*strDest++=*strSrc++)
    {
        NULL;//该循环条件内可以用++，
    }//此处可以加语句*strDest=’\0’;无必要
    return address;//为了实现链式操作，将目的地址返回
}

*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{	
	char src[] = "abc";
	char dest[] = {'1','2','\0','3','4','\0'};
	
//	strcat(src, dest);
//	printf("str:%s\n", src);

	strcat(src+1, dest+1);
	printf("str:%s\n", src);
	
	char p1[15]= "abcd",*p2= "ABCD", str[50]= "xyz"; 
	strcpy(str+2,strcat(p1+2,p2+1)); 
	printf("%s\n",str);

	return 0;
}
