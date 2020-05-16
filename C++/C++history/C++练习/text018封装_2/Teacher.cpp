#include"Teacher.h"

Teacher::Teacher(string name,int age,int m):m_strName(name),m_iAge(age),m_iMax(m)
{
	cout<<"Teacher::Teacher(string name,int age,int m)"<<endl;
}

int Teacher::getMax()
{
	return m_iMax;
}

void Teacher::setName (string name)
{
	m_strName=name;
}

string Teacher::getName()
{
	return m_strName;
}

void Teacher::setAge(int age)
{
	m_iAge=age;
}

int Teacher::getAge()
{
	return m_iAge;
}