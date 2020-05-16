#include<iostream>
#include<string>
using namespace std;

class Student
{
public:
protected:
	int num;
	string name;
	char sex;
};

class Student1:protected Student
{
public:
	void get_value1();
	void display1();
private:
	int age;
	string addr;
};

void get_value1()
{
	cout<<"cin>>num>>name>>sex>>age>>addr"<<endl;
	cin>>num>>name>>sex;
	cin>>age>>addr;
}

void display1()
{
	cout<<"num"<<num<<endl;
	cout<<"name"<<name<<endl;
	cout<<"sex"<<sex<<endl;
	cout<<"age"<<age<<endl;
	cout<<"addr"<<addr<<endl;
}

int main()
{
	Student1 stu1;
	stu1.get_value1();
	stu1.diaplay1();
	system("pause");
	return 0;
}
