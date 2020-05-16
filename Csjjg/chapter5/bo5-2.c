#include"c5-2.h"


//创建稀疏矩阵的三维数组
Status CreateSMatrix( TSMatrix *M)
{
    int i,m,n;
    ElemType e;
    Ststus k;
    printf("请输入矩阵的行数,列数,非零元素数：");
    scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
    (*M).data[0].i = 0;
    for(i = 1;i<=(*M).tu;i++)
    {
        do
        {
            printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu); 
            scanf("%d,%d,%d",&m,&n,&e);
            k = 0;
            if(m<1||m>(*M).mu||n<1||n>(*M).nu)
            {//插入的行或列位置非法
                k =1;
            }
            if(m<(*M).data[i-1].i|| m == (*M).data[i-1].i&&n<=(*M).data[i-1].j)
            {//比上一次插入的行号或列号小，即行号或列号的顺序有误
                k = 1;
            }
        } while (k);//正确插入位置后才可以插入
        (*M).data[i].i = m;
        (*M).data[i].j = n;
        (*M).data[i].e = e;
    }//for
    return OK;
}

//销毁矩阵
void DestroySMatrix(TSMatrix *M)
{
    (*M).mu = 0;
    (*M).nu = 0;
    (*M).tu = 0;
}


//输出稀疏矩阵
void PrintSMatrix(TSMatrix M)
{
    int i ;
    printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
    printf("行  列  元素值\n");
    for (i = 1; i <= M.tu; i++)
    {
        printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
    }
}

//复制
Status CopySMatrix(TSMatrix M,TSMatrix *T)//要进行参数传递的都用指针表示
{
    (*T) = M;
    return OK;
}

int comp(int c1,int c2) /* 另加 */
 { /* AddSMatrix函数要用到 */
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

