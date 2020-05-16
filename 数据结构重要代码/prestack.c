
// 非遞歸先序遍歷
void prestack(BiTree T)
{
    Initstack(S);
    BiTree p = T;
    if(isEmpty(p))
        return;
    else
        push(S,p);
    while(isEmpty(p))
    {
        pop(S,p);
        visit(p);
        if(p->rchild)
            push(S,p->rchlid);
        if(p->lchild)
            push(S,p->lchild);
    }

}


//非递归后续遍历