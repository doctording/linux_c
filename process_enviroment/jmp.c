#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

void fun1(void);
void fun2(void);
jmp_buf jmpbuffer;

void main(void)
{
    int i = 0;
    int j = 0;
    i = setjmp(jmpbuffer);
    if(i==0)
    {
        printf("first run\n");
        fun1();
        fun2();
    }
   else
   {
     switch(i)
     {
       
     case 1:
       printf("In fun1 \n");
     break;
   case 2:
     printf("In fun2\n");
     break;
   default:
     printf("unkown error\n");
     break;
     }
          exit(0);
   }
    return 1;
} 

void fun1(void)
{
    char *s = "hello";
    char *s1 = "Hello";
    if(strcmp(s,s1)!=0)
    longjmp(jmpbuffer,1);
}

void fun2(void)
{
    char *s = "world";
    if(strcmp(s,"World")!=0)
    longjmp(jmpbuffer,2);
}
