//判断平衡二叉树
#include<staio.h>

typedef struct 
{
    int hight;
    int key;
    struct BiNode *lchild,*Rchild;    
}BiNode,*BiTree;

int hleft,hright,a[2],b1[2],b2[2];

int[] judge_AVL(BiTree *T)
{
    if(T == null)
    {
        T->height =0;
        T->key = 1;
        a[0] = T->height;
        a[1] = T->key;
        return a;        
    }
        
    else if(T->lchild == null && T->rchild == null)
    {
        T->height = 1;
        T->key = 1;
        a[0] = T->height;
        a[1] = T->key;
        return a;         
    }
    else
    {
        b1 = judge_AVL(T->lchild);
        b2 = judge_AVL(T->rchild);
        T->height = (b1[0] > b2[0])?(b1[0] +1 ): (b2[0] +1);
        T->key = (b1[1]==1&&b2[1]==1)? 1:0;
        a[0] = T->height;
        a[1] = T->key;
        return a;
    }   
}



//或者
BiTree judge_AVL(BiTree *T)
{
    if(T == null)//当前为空结点
    {
        T->height =0;
        T->key = 1; 
        return T;     //这个返回没有意义，只是为了格式
    }
        
    else if(T->lchild == null && T->rchild == null)//当前节点为叶结点，则将树深度置为1，key表示是否平衡
    {
        T->height = 1;
        T->key = 1;
        return T;         
    }
    else
    {
        judge_AVL(T->lchild);
        judge_AVL(T->rchild);
        T->height = (T->lchild->height > T->rchild->height)?(T->lchild->height +1 ): (T->rchild->height+1);
        T->key = (T->lchild->key==1&&T->rchild->key==1)? 1:0;
        return T;//返回根节点
    }   
}


