#include"Teacher.h"

Teacher::Teacher(string name,int age):m_strName(name),m_iAge(age)
{
	cout<<"Teacher(string name,int age)"<<endl;
}

void Teacher::setName(string _name)//姓名
{
	m_strName=_name;
}
string Teacher::getName()
{
	return m_strName;
}
void Teacher::setGender(string _gender)//性别
{
	m_strGender=_gender;
}
string Teacher::getGender()
{
	return m_strGender;
}
void Teacher::setAge(int _age)//年龄
{
	m_iAge=_age;
}
int Teacher::getAge()
{
	return m_iAge;
}
void Teacher::teach()
{
	cout<<"现在上课"<<endl;
}