#include<iostream>
#include<stdlib.h>
#include"Array.h"

using namespace std;

Array::Array(int len)
{
	m_iLen=len;
}

Array::~Array()
{

}

void Array::setLen( int len)
{ 
	m_iLen=len;
}

int Array::getLen()
{
	return m_iLen;
}

Array& Array::printInfo()
{
	cout<<"len="<<m_iLen<<endl;
    return *this;//this本来就是函数Array的指针，加'*'号后就是函数本身，符合函数的返回类型：类
}