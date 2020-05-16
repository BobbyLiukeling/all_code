/* 
对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数 
2019.5.4
p48
*/

typedef int SElemType;
#include"c1.h"
#include"c3-1.h"//定义栈的结构
#include"bo3-1.c"//栈的基本操作

void conversion()
{
    SqStack s;
    unsigned n;
    SElemType e;
    InitStack(&s);
    printf("n(>=0)=");
    scanf("%u",&n);//输入非负的十进制数
    while(n)//当n不等于0 
    {//所有余数入栈
        Push(&s,n%8);//入栈n除以8的余数(8进制的低位)
        n= n/8;
    }
    while(!StackEmpty(s))//当栈不为空时
    {
        Pop(&s,&e);//将栈元素弹出并赋值给e
        printf("%d",e);//输出e
    }
    printf("\n");
}

void main()
{
    conversion();
}