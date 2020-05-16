#define LIST_INIT_SIZE 10//线性表存储空间的分配、
#define LISTINCREMENT 2 //存储空间线性表分配每次增量
typedef struct 
{
    ElemType *elem; //线性表基址，在此ElemType在其他地方被定义为int类型
    int length; //当前长度
    int listsize; //当前分配的存储容量以sizeof（ElemType）为单位,总共分配的单位数
}SqList ;
