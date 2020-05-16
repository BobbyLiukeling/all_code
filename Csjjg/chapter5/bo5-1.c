#include"C5-1.H"
Status InitArray(Array *A,int dim,...)
{
    int elemtotal =1 i;//elemtotal 是元素的总值
    va_list ap;//可变参数关键字为va_list 作用类似以int
    if (dim<1||dim >MAX_ARRAY_DIM){
        return ERRER;
    }//检查维度是否合法
    (*A).dim = dim;
    //如果是三维，bounds就只需要存三个int类型的数据
    //同理 四维存四个
    (*A).bounds = (int *) malloc (dim *sizeof(int))
    if(!(*A).bounds)
        exit(OVERFLOW);
    va_start(ap,dim);
    for(i = 0; i<dim; ++i)
    {
        (*A).bounds[i] = va_arg(ap,int);
        if ((*A).bounds[i]<0)
            return UNDERFLOW;//维度必大于0
        elemtotal * = (*A).bounds[i];//所有元素值，为传入维数之积
    }//for
    va_end(ap);
    (*A).base = (ElemType *) malloc (elemtotal * sizeof (int));
    if(!(*A).base)
        exit(OVERFLOW);
    (*A).constants = (int *).malloc(dim * sizeof(int));
    if(!(*A).constants)
        exit(OVERFLOW);
    (*A).constants[dim-1] = 1;
    for(i = dim-2 ; i>=0; --i)
        (*A).constants[i] = (*A).bounds[i+1]*(*A).constants[i+1];
    return OK;  
    
}