#include <stdlib.h>  
#include <stdio.h>  

#define SIZE 8000000L   //数组长度  
 
int main()  
{  
    struct timeval start,end;  
    long long startusec,endusec;  
    double elapsed;  
    int i;  
    int *a = (int *)malloc(SIZE*sizeof(int));  //动态分配数组  
    
    gettimeofday(&start,NULL);//获得起始时间  

    for(i=0;i<SIZE;i++)  
    {
        a[i] = i;  
    }  
    
    gettimeofday(&end,NULL);//获得结束时间  
    for(i=0;i<SIZE;i++)//打印数组内容  
    //printf("%d ",a[i]);  
      
    startusec = start.tv_sec * 1000000 +  start.tv_usec;  
    endusec = end.tv_sec * 1000000 + end.tv_usec;  
    elapsed = (double)(endusec-startusec)/1000000.0;//计算处理所花费的时间  
    printf("sort took %.4f seconds\n",elapsed);  
  
    return 0;  
}  
