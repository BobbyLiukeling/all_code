typedef enum{Link,Thread}Pointertag;//枚举类型
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild; 
    Pointertag LTag, RTag;
} BiThrNode, *BiThrTree;
