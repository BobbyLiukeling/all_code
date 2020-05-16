#include<iostream>
using namespace std; 
class Date;
class Time
{
public:
	Time(int ,int,int);
	void display(Date &);
private:
	int hour;
	int minute;
	int sec;
};

class Date
{
public:
	Date(int,int,int);
	friend void Time::display(Date&);//声明Time中的display函数为本类的友元函数成员
private:
	int month;
	int day;
	int year;
};

Time::Time(int h,int m,int s)
{
	hour=h;
	minute=m;
	sec=s;
}

void Time::display(Date &d)
{
	cout<<d.month<<"/"<<d.day<<"/"<<d.year<<endl;
	cout<<hour<<":"<<minute<<":"<<sec<<endl;//引用本类对象中的私有成员
}

Date::Date(int m,int d,int y)
{
	month=m;
	day=d;
    year=y;
}
int main()
{
	Time t1(10,13,24);
	Date d1(12,25,2007);
	t1.display(d1);
	system("pause");
	return 0;
}
