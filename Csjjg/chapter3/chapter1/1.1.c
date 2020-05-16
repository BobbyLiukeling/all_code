/*
计算x+.....+n的运行时间
*/
#include<stdio.h>
#include<stdlib.h>
void main()
{
    struct timeb t1,t2;
    long t;
    double x,sum = 1, sum1;
    int i,j,n;
    printf("请输入起始值x，和最终值n：")；
    scanf("%lf%d",&x,&n);
    ftime(&t1);//求得当前时间
    for(i = 1;i<=n;i++)
    {
        sum1 = 1;
        for(j = 1;j<=i;j++)
        {
            sum1 = -sum1/x;
            sum+ = sum1;
        }
    }
    
}