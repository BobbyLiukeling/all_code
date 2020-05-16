#include<iostream>
#include<string>
using namespace std;

class Student
{
public:
	Student(int n,string nam,char s)
	{
		num=n;
		name=nam;
		sex=s;
		cout<<"Constructor called"<<endl;
	}

	~Student()//析构函数
	{
		cout<<"Destructor called"<<endl;//刷屏
	}

	void display()
	{
		cout<<"mun:"<<num<<endl<<"name:"<<name<<endl<<"sex"<<sex<<endl;
	}

private:
	int num;
	string name;
	char sex;

};


int main()
{
	Student stud1(10010,"wangli",'f');//建立对象，注意字符的初始化方式
	stud1.display();
	Student stud2(10020,"wangli",'m');//建立对象，注意字符的初始化方式
	stud2.display();
	system("pause");
    return 0; 
}