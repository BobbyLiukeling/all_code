/*
2019.4.29
顺序表示的线性表的基本操作
*/

//构造一个空的线性表
Status InitList(SqList *L)
{
    (*L).elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));//申请空间
    if(!(*L).elem)
        exit(OVERFLOW);//分配失败
    (*L).length = 0;//空表长度为0
    (*L).listsize = LIST_INIT_SIZE;//每个单位的存储容量
    return OK;
}//InitList

//线性表已经存在，销毁线性表
Status DestroyList(SqList *L)
{
    free ((*L).elem);
    (*L).elem;
    (*L).length = 0 ;
    (*L).listsize = 0;
    return OK;
}//DeastroyList

//线性表已经存在，将线性表置空】
Status ClearList(SqList *L)
{
    (*L).length = 0;
    return OK;
}//ClearList


//判断线性表是否为空，若为空则返回TRUE
Status ListEmpty(SqList L)
{
    if(L.length == 0)
        return TRUE;
    else
      return FALSE;    
}//ListEmpty


//返回L中数据元素的个数
int ListLength(SqList L)
{
    return L.length;
}//ListLength


//返回L中第i个元素的值
Status GetElem(SqList L,int i,ElemType *e)
{
    if(i<1||i>L.length)
        exit(ERROR);
    *e = *(L.elem+i-1);
    return OK;
}//GetElem


//输入一个元素e，返回线性表中第一个e的位置，如果e不存在，则返回0
int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    ElemType *p;
    int i = 1;//除头结点的第一个节点
    p = L.elem;//p的初值为第一个元素的存储位置
    while(i<=L.length&&!compare(*p++,e))
        ++i;
    if(i<=L.length)//找到元素
        return i;
    else
        return 0;

}//LocateElem

//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， 否则操作失败，pre_e无定义
Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
{
    int i =2;
    ElemType *p = L.length+1;
    while(i<=L.length&&*p!=cur_e)//遍历寻找cur_e元素
    {
        p++;
        i++;
    }//while
    if(i>L.length)
        return INFEASIBLE;
    else 
    {
        *pre_e = *--p;//返回前驱
        return OK;
    }//else
}//PriorElem


//若cur_e是L的数据元素，且不是L中的最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义 
Status NextElem(SqList L, ElemType cur_e,ElemType *next_e)
{
    int i = 1;
    ElemType *p = L.elem;
    while (i<L.length && *p != cur_e)//遍历寻找cur_e元素
    {
        i++;
        p++;
    }//while
    if(i==L.length)
        return INFEASIBLE;
    else
    {
        *next_e = *++p;
        return OK;
    } //else   
}//NextElem


//操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 
Status ListInsert(SqList *L,int i,ElemType e)//算法2.3
{
    ElemType *newbase,*q,*p;
    if(i<1||i>(*L).length+1)//插入位置不合法
        return ERROR;
    if((*L).length>=(*L).listsize)//申请的存储单位使用完了，增加分配
    {
        /*
            void *realloc(void *ptr, size_t size);
            realloc() 会将 ptr 所指向的内存块的大小修改为 size，并将新的内存指针返回。
        */
        newbase = (ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)//申请新存储空间失败
            exit(OVERFLOW);
        (*L).elem = newbase;
        (*L).listsize+=LISTINCREMENT;        
    }//if
    q = (*L).elem+i-1;//数据插入的位置
    for (p = (*L).elem+(*L).length; p>=q;--p ) 
    {//将i位置后的数据向后移，以便新的数据插入
        *(p+1) = *p;
    }
    *q = e;//在移动完数据后插入新数据e，
    ++(*L).length;
    return OK;    
}//ListInsert


//删除第i个元素，并返回其值，同时将线性表的长度减一
Status ListDelete(SqList *L,int i,ElemType *e)//算法2.4
{
    ElemType *p,*q;//p,q为int类型指针
    if(i<1||i>(*L).length)//删除位置不合法
        return ERROR;
    p = (*L).elem+i-1; //删除元素的位置
    *e = *p;//将被删除元素的值取出
    q = (*L).elem+(*L).length-1;//线性表尾位置
    for(++p;p<=q;++p)//将制定删除的位置i的元素都向前移动
        *(p-1) = (*p);
    (*L).length--;
    return OK;
}//ListDelete


//依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 
// vi()的形参加'&'，表明可通过调用vi()改变元素的值 
Status ListTraverse(SqList L, void(*vi)(ElemType*))
{
    ElemType *p;
    int i;
    p = L.elem;
    for(i = 1;i<l.length;i++)
        vi(p++);
    printf("\n");
    return OK;
}//ListTravwese