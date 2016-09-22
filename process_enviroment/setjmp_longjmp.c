#include <stdio.h> 
#include <setjmp.h>

jmp_buf buf;

void banana(){ 
    printf("in banana() \n"); 
    longjmp(buf,1);// 跳转，后面的语句都不会执行
    printf("you'll never see this,because i longjmp'd");
}

int main() 
{ 
    if(setjmp(buf)) // 接收longjmp传来的jmp_buf
        printf("back in main\n"); 
    else{ 
        printf("first time through\n"); 
        banana(); 
    }
    return 0;
}
/*
goto只在函数体内跳来跳去
setjmp/longjmp可以跳跃函数
*/
