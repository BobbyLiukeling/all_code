//孩子兄弟表示法存储的树的深度
#include<staio.h>

typedef struct 
{
    int data;
    TNode *child,*lbrather;
}TNode,*Tree;

int deep,left,right;
int deep_tree(Tree *T)
{
    if(T == null)
        return 0;
    else
    {
        child = deep_tree(T->child);
        brather = deep_tree(T->lbrather);
        return (child+1>brather)? child+1 : brather;

    }
    
}
