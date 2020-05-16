#include<iostream>
#include<vector>
#include"matrix.h"
using namespace std;

matrix::matrix()//无参构造函数
{
	length = 1;
	width = 1;
	arr.push_back(vector<int>(0));
}

matrix::matrix(int l, int w)//重载构造函数
{
	length = l;
	width = w;
	arr.resize(length, vector<int>(width));
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width;j++)
	{
		arr[i][j] = rand() % 1000;
	}
}

matrix matrix::operator+(matrix &m1)
{
	matrix m3;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
		{
		m3.arr[i][j] = arr[i][j] + m1.arr[i][j];
		}
	return m3;
}

void matrix::putmatrix()//输出矩阵
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
}

matrix::~matrix()
{
	cout <<" ~matrix" << endl;
}