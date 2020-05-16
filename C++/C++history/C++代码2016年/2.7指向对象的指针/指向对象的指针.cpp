#include<iostream>
using namespace std;

class Time
{
public:
	Time (int ,int,int);//声明构造函数
	int hour;
	int minute;
	int sec;
	void get_time();

};

Time::Time(int h,int m,int s)
{
    hour=h;
	minute=m;
	sec=s;
}

void Time::get_time()
{
	cout<<hour<<":"<<minute<<":"<<sec<<endl;
}

int main()
{
	Time t1(10,34,25);
	int *p1=&t1.hour;
	cout<<*p1<<endl;
	t1.get_time();
	Time *p2=&t1;
	p2->get_time();
	void(Time::*p3)();//没看懂，指向类公有成员的函数变量指针，
	p3=&Time::get_time;//没看懂，使p3指向类公用成员函数get_time
	(t1.*p3)();
	system("pause");
	return 0;
}


