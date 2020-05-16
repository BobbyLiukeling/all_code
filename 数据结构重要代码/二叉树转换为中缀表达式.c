#include<stdio.h>
//将已知二叉树转换为中缀表达式

typedef struct 
{
    char data[10];
    struct  node *left,*right;
    
}node,BTree;

void middleexpree(BTree *T)
{
    if(T == null)
        return ;
    else
    {
        printf("(");
        middleexpree(T->left);
        for(int i = 0; i<len(T->data);i++)
            printf("%s",T->value[i]);
        middleexpree(T->right);
        printf(")");
    }   
    
}
