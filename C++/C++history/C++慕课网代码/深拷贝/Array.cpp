#include<iostream>
#include"Array.h"
using namespace std;

Array::Array(int count)
{
	m_iCount=count;
	m_pArr=new int[m_iCount];
	for(int i=0;i<m_iCount;i++)
	{
		m_pArr[i]=i;
	}
	cout<<"Array"<<endl;
}

Array::Array(const Array &arr)
{
	m_iCount=arr.m_iCount;
	m_pArr=new int[m_iCount];
	for(int i=0;i<m_iCount;i++)
	{
		m_pArr[i]=arr.m_pArr[i];//内存所指向值的赋值
	}

	cout<<"Array &"<<endl;
}
Array::~Array()
{
	delete []m_pArr;
	m_pArr=NULL;
	cout<<"~Array()"<<endl;
}

void Array::setCount(int count)
{
	m_iCount=count;
}

int Array::getCount()
{
	return m_iCount;
}

void Array::printAddr()
{
	cout<<"m_pArr的值是"<<m_pArr<<endl;
}
