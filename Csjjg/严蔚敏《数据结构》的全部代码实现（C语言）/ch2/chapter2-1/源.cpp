/* algo2-1.c ʵ���㷨2.1�ĳ��� */
#include"c1.h"
typedef int ElemType;
#include"c2-1.h" /* �������Ա�Ķ�̬����˳��洢�ṹ */
//#include"bo2-1.c" /* ����ʹ��bo2-1.c�еĻ������� */

Status InitList(SqList* L) /* �㷨2.3 */
{ /* �������������һ���յ�˳�����Ա� */
	(*L).elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
		exit(OVERFLOW); /* �洢����ʧ�� */
	(*L).length = 0; /* �ձ���Ϊ0 */
	(*L).listsize = LIST_INIT_SIZE; /* ��ʼ�洢���� */
	return OK;
}

int main()
{
	cout<<"hello,world!"
	return 0;
}