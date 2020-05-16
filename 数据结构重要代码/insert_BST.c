//向二叉排序树中插入关键字key
#include<stdio.h>
 typedef struct BST
 {
     int data;
     BiNode *lchild,*rchild;
 }BiNode,*BiTree;

 int Insert_BST(BiTree *T,int key)
 {
     if( T == null)
     {
         BiNode = (BiTree)malloc(sizeof(BiNode));
         T->data = key;
         T->lchild = T->rchild = null;
         return 1;
     }

     if(T->data == key)
        return 0;
    else if (T->data>key)       
        Insert_BST(T->lchild,key);
    else
    {
        Insert_BST(T->rchild,key);
    }
    return 1;
     
 }


//构造二叉树

