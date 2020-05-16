/*
栈的顺序存储表示
*/
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
typedef struct SqStack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;
