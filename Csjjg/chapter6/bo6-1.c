#include"c6-1.h"
#define Nil ' '
#include"c1.h"

//构造一个空的二叉树
Status InitBiTree(SqBiTree T)
{
    int i;
    for(i = 0;i<MAX_TREE_SIZE;i++)
        T[i] = Nil;//初始化为空，Nil值在main中会对其进行定义
    return OK;
}//InitBiTree

void DestroyBiTree()
{
    //由于数组为定长类型，所以无法销毁
}


//按层序次序输入二叉树中节点的值
Status CreateBiTree(SqBiTree T)
{
    int i = 0;
    #if CHAR
        int 1;
        
}