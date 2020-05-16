#include<iostream>
#include<string>

using namespace std;

class Teacher
{
public:
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

int main()
{
	Teacher t;
	t.setName("我的天");
	t.setGender("男");
	t.setAge(0);
	cout<<t.getName()<<"  "<<t.getGender()<<"  "<<t.getAge<<endl;
//	t.taech(); 
	system("pause");
	return 0;
}
