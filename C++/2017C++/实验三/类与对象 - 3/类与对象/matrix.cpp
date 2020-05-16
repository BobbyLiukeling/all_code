#include<iostream>
#include"matrix.h"

using namespace std;

matrix::matrix()//无参构造函数
{
	length = 1;
	width = 1;
	memset(a, 0,sizeof(a));
}

matrix::matrix(int l, int w)//重载构造函数
{
	length = l;
	width = w;
	a=new int *[width];
	for (int i = 0; i < width; i++)
		a[i] = new int[length];
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width;j++)
	{
		a[i][j] = rand() % 1000;
	}
}

matrix matrix::operator+(matrix &m1)
{
	matrix m3;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
		{
		m3.a[i][j] = a[i][j] + m1.a[i][j];
		}
	return m3;
}

void matrix::putmatrix()//输出矩阵
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << a[i][j];
		}
		cout << endl;
	}
}

matrix::~matrix()
{
	for (int i = 0; i < width; i++)
	{
		delete a[i];
		a[i] = NULL;
	}
	delete [width]a;
	a = NULL;
	cout <<" ~matrix" << endl;
}