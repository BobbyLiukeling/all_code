/*	实验目的和要求
掌握对象的调用方法，理解并熟练使用友元，掌握运算符重载的方法
	主要实验方法
编写程序，实现2个矩阵的加减法，并输出结果。要求：
①重载运算符“+”、“-”、“<<”和“>>”；
②分别使用成员函数和友元函数实现矩阵的加减法；
编写程序，定义body类，记录班上学生的身体健康状况，要求：
①需使用对象数组；
②body类的数据成员参考体检项目；
③body类的函数成员除输入和输出外，应有健康状况的评价。
*/
#include <iostream>
using namespace std;
#include"matrix.h"


int main()
{
	matrix a, b, c,d;
	a.input();
	b.input();
	cout << endl << "matrix a:" << endl;
	a.display();
	cout << endl << "matrix b:" << endl;
	b.display();
	c = a + b;                                         //用重载运算符“+”实现两个矩阵相加
	cout << endl << "matrix c = matrix a + matrix b :" << endl;
	c.display();
	d = a - b;                                         //用重载运算符“+”实现两个矩阵相加
	cout << endl << "matrix d = matrix a - matrix b :" << endl;
	d.display();

	getchar();
	return 0;
}