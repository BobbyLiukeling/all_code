#include<stdio.h>

//计算带权路径长度，结点数据结构，和算法思想
//WPL 是树中所有叶结点带权路径长度之和，叶结点
typedef struct
{
    int value;
    struct BiNode *lchild,*rchild;    
}BiNode,*BiThree;

int left,right,high;

int totleWPL(BiThree *T,int deep)//带权路径长度，计算时记得深度
{
    if(T == null)
        return 0;
    else if(T->lchild = null && T->rchild == null)//为叶结点
        return T->value*deep;
    else//非叶结点
    {
        left = totleWPL(T->lchild , deep+1);
        right = totleWPL(T->rchild , deep+1);
        return left + right;
    }
    
}
