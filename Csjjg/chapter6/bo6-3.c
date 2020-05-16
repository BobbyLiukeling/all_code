Status CreateBiThrTree(BiThrTree *T)//构造二叉搜索树
{
    TElemType h;
    #if CHAR
        scanf("%c",&h);
    #else
        scanf("%d",&h);
    #endif
        if(h == Nil)
            *T = NULL;
        else
        {
            *T = (BiThrTree)malloc(sizeof(BiThrTree));
            if(!*T)
                exit(OVERFLOW);
            *T->data = h;//先序遍历
            CreateBiThrTree(&(*T)->lchild);//递归构造左孩子
            if((*T)->lchild)//若果有左孩子
                (*T)->LTag = Link;
            CreateBiThrTree(&(*T) -> rchild);
            if((*T) -> rchild)
                (*T) -> RTag = Link;
        }//else
        return OK;        
}