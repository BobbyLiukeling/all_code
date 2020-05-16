/*构造一个空栈*/
#include "c1.h"
#include"c3-1.h"
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType *)malloc (STACK_INIT_SIZE*sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base; //空栈，栈顶等于栈底
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}


//销毁栈
Status DestoryStack(SqStack *S)
{
    free (*S).base;
    (S*).base = NULL;
    (*S).top = NULL;
    (*S).stacksize = 0;
    return OK;
}

//判断栈是否为空
Status StackEmpty(SqStack S)
{
    if(S.top == S.base)
        return TRUE;
    else 
        return FALSE;
}


//将栈置空
Status ClearStack(SqStack *S)
{
    /*
    在调用malloc的时候，
    系统会记住你申请的这块连续空间的起始地址以及这块空间的大小，
    释放free的时候，只要把这个起始地址告诉系统，
    系统自然就知道要释放多大的空间
    */
    (*S).top = (*s).base;
    return OK;
}


/* 
若栈不空，则用e返回S的栈顶元素，并返回OK；
否则返回ERROR 
*/
int Status GetTop(SqStack S, SElemType *e)
{
    if(S.top>S.base)//栈不为空
    {
        *e = *(S.top - 1);//top = -1时，为空栈
        return OK;
    }
    else
        return ERROR;
}


/* 插入元素e为新的栈顶元素 */
Status Push(SqStack *s,SElemTyp e)
{
    if ((*S).top-(*S).base>= (*S).stacksize)
    {//栈满，追加空间
        (*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!(*S).base)
            exit(OVERFLOW);
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize += STACKINCREMENT//栈的容量更新        
    }
    *((*S).top)++ = e;
    return OK;
}


/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return ERROR;
    *e = *--(*S).top;
    return OK;
}


Status StackTraverse(SqStack S,Status(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   /* 一旦visit()失败，则操作失败 */
   while(S.top>S.base)
     visit(*S.base++);
   printf("\n");
   return OK;
 }