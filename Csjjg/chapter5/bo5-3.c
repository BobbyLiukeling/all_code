#include"C5-3.H"


//稀疏矩阵的快速转置
Status TransposeSMatrix(RLSMatrix M,RLSMatrix *T)
{
    int p,q,t,col,*num;
    num = (int *)malloc((M.nu + 1)*sizeof(int));
    (*T).mu = M.nu;
    (*T).nu = M.mu;
    (*T).tu = M.tu;
    if((*T).tu)
    {
        for(col = 1;col<=M.nu;++col)
            num[col] = 0;//每列的元素个数初始化为0；
        for(t = 1;t<=M.tu;++t)
            ++num[M.data[t].j];//求每列的非零元素个数
        (*T).rpos[1] = 1;//第一个非零元素在M.data中的位置一定是1
        for(col = 2;col<= M.nu;++col)
            (*T).rpos[col] = (*T).rpos[col-1] + num[col-1];
        for(col = 1;col<=M.nu;++col)
            //将原来每行的第一个元素位置，转换为现在的每列的第一个元素位置
            num[col] = (*T).rpos[col];
        for(p = 1;p<=M.tu;++p)
        {
            col = M.data[p].j;//当前的行号
            q = num[col];//当前行（已转化为列）中元素的第一个元素位置
            (*T).data[q].i=M.data[p].j;
            (*T).data[q].j=M.data[p].i;
            (*T).data[q].e=M.data[p].e;
            ++num[col];//将当前列的第一个元素的位置往后移动一位，为下次计算准备
        }//for
        free(num);
        return OK;
    }
}