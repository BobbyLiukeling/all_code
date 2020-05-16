#include<iostream>
#include<string>
using namespace std;
class Teacher
{
public:
	Teacher(string name ="Jim",int age=10,int m=100);
	void setName(string name);
	string getName();
	void setAge(int age);
	int getAge();
	int getMax();
private:
	string m_strName;
	int m_iAge;
	const int m_iMax;
};