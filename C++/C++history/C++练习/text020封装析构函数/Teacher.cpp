#include"Teacher.h"

Teacher::Teacher(string name,int age):m_strName(name),m_iAge(age)
{
	cout<<"Teacher::Teacher(string name,int age,int m)"<<endl;
}

Teacher::Teacher(const Teacher &tea)//¿½±´¹¹Ôìº¯Êý
{
	cout<<"Teacher(const Teacher&tea);"<<endl;
}

Teacher::~Teacher()
{
	cout << "~Teacher()" << endl;
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