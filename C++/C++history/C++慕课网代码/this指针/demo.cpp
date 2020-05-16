#include<iostream>
#include<stdlib.h>
#include"Array.h"

using namespace std;

/*Array类
    数据成员：m_iLen表示数组长度
	成员函数
	   构造函数
	   析构函数
	   len的封装函数
	   信息输出函数printinfo
*/



int main()
{
	Array arr1(10);
	arr1.printInfo().setLen(5);/*
							   首先打印实例化所传入的参数10，然后返回一个指向arr1类的指针，
	                           接着是“.setLen(5)”,调用类中的封装函数，传入的参数发生了变化变为了5，
	                           最后打印出对象len的值
	                           */
	cout<<arr1.getLen()<<endl;
	system("pause");
	return 0;
}