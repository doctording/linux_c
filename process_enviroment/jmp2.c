/*
http://blog.chinaunix.net/uid-20357359-id-1963625.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

static jmp_buf jmpbuf_1;

int g_a = 0;

void test(int index, int *local_val)
{
    g_a = 1111;
    *local_val = 2222;
    longjmp(jmpbuf_1,index);
}

int main(int argc, char *argv[])
{
    int ret = 0, index = 0;
    int l_a=1;

    if(argc!=2)
        index = 1;
    else
    {
        index = atoi(argv[1]);
        if(index==0 || index>2)
            index = 1;
    }

    ret = setjmp(jmpbuf_1);

    if(ret == 0)
    {
        printf("Orig setjmp\n");
    }
    else if(ret == 1)
    {
        printf("Return From longjmp 1\n");
        printf("Global_a: %d\n", g_a);
        printf("Local_a: %d\n", l_a);

        return 0;
    }
    else if(ret == 2)
    {
        printf("Return From longjmp 2\n");
        printf("Global_a: %d\n", g_a);
        printf("Local_a: %d\n", l_a);

        return 0;
    }
    
    test(index, &l_a);

    return 0;
}
