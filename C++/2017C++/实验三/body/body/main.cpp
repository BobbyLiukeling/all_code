#include<iostream>
#include<vector>
#include"body.h"
using namespace std;

//掌握对象的调用方法，理解并熟练使用友元，掌握运算符重载的方法
//编写程序，定义body类，记录班上学生的身体健康状况，要求：
//①需使用对象数组；
//②body类的数据成员参考体检项目；
//③body类的函数成员除输入和输出外，应有健康状况的评价。


int main()
{
	body b[3];
	for (int i = 0; i < 3;i++)
	{ 
	b[i].getbody();
	cheakbody(b[0]);
	}

	getchar();
	return 0;
}
