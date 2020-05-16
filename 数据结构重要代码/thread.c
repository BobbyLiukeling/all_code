void Inthread(BiNode T,BINode pre)//都是节点类型，线索化都是针对结点
{
    if(T)//当前线索化结点不为空
    {
        Inthread(T->lchild);//和中序遍历一样，先递归左子树
        
        //对当前节点进行线索化处理
        if(T->lchild == null)
        {
            T->lchild = pre;//
            T->ltag = 1;
        }
        if(pre!=null && pre->rchild == null)//将pre的右子树线索化为当前子树
        {
            pre->rchild = T;
            pre->rtag =1;
        }

        //对有子树进行线索化
        pre = T;//修改当前的前驱指针（根据中序遍历规则右子树的前驱一定是当前指针）
        Inthread(T->rchild);
    }
}

//初始化当前遍历
void midleThread(Bithree T)
{
    BiNode pre = null;
    if (T)
    {
        Inthread(T,pre);
        //扫尾
        pre->rchild = null;
        pre->rtag = 1;
    }
}