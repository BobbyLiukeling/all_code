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
#include<iostream>
#include"matrix.h"
using namespace std;

int main()
{
	matrix mt1(2, 2);
	matrix mt2(2, 2);
	matrix mt3;
	mt3 = mt1 + mt2;
	cout << "this is the first matrix arry1[2][2]:"<< endl;
	mt1.putmatrix();
	cout << "this is the first matrix arry2[2][2]:" << endl;
	mt2.putmatrix();
	cout << "this is the first matrix arry3[2][2]=arry1[2][2]+arry2[2][2]:" << endl;
	mt3.putmatrix();

	getchar();
	return 0;
}