/* algo2-1.c 实现算法2.1的程序 */
#include"c1.h"
typedef int ElemType;
#include"c2-1.h" /* 采用线性表的动态分配顺序存储结构 */
//#include"bo2-1.c" /* 可以使用bo2-1.c中的基本操作 */

Status InitList(SqList* L) /* 算法2.3 */
{ /* 操作结果：构造一个空的顺序线性表 */
	(*L).elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
		exit(OVERFLOW); /* 存储分配失败 */
	(*L).length = 0; /* 空表长度为0 */
	(*L).listsize = LIST_INIT_SIZE; /* 初始存储容量 */
	return OK;
}

int main()
{
	cout<<"hello,world!"
	return 0;
}