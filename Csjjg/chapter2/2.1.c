//https://wenku.baidu.com/view/447e9274650e52ea551898ad.html
//代码网址
/*
2019.4.29
将两个按非递减排列的线性表LA和LB合并成为新的线性表LC，且LC也按照非递减方式排列
*/                                                                            
#include "c1.h"
typedef int ElemType;//定义ElemType 为int类型
#include"c2-1.h"
#include"bo2-1.c"//一般基本操作


//判断两个数是否相等
Status equal(ElemType c1,ElemType c2)
{
    if(c1 == c2)
        return TRUE;
    else
    {
        return FALSE;
    }
    
}//equal

//将La表与Lb表合并到La表中
void Union(SqList *La,SqList Lb)
{
    ElemType  e;
    int La_len,Lb_len;
    int i;

    //求两个线性表长度
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    for(i = 1;i<Lb_len;i++)
    {
        GetElem(Lb,i,&e);//将第i个元素取出并赋值给e，每次变量e的值都会被修改
        if(!LocateElem(*La,e,equal))//在a中没找到b的元素，则插入
            ListInsert(La,++La_len,e);//在La的末尾插入
    }//for
}

void print(ElemType *c)
{
    printf("%d",*c);//打印c的值
}

void main()
{
    SqList La,Lb;
    Status i;
    int j;
    i = InitList(&La);
    if( i == 1)//创建La表成功（空表）
        for(j = 1;j<=5;j++)        
            i = ListInsert(&La,j,j);//初始化La
    printf("La  = ");
    ListTraverse(La,print);
    i = InitList(&Lb);
    if( i == 1)//创建La表成功（空表）
        for(j = 1;j<=5;j++)
            i = ListInsert(&Lb,j,j*2);//初始化Lb
    printf("Lb  = ");
    ListTraverse(Lb,print);
    Union(&La,Lb);
    printf("new La = ");
    ListTraverse(La,print);
}