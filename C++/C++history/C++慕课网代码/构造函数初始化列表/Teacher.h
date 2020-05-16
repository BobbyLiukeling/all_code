#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;

class Teacher
{
public:
	Teacher(string name="Jim",int age=20);
	void setName(string _name);//姓名
	string getName();
	void setGender(string _gender);//性别
	string getGender();
	void setAge(int _age);//年龄
	int getAge();
	void teach();
private:
	string m_strName;
	int m_iAge;
	string m_strGender;
};