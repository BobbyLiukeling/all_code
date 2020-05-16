#include<iostream>
using namespace std;

class Time
{
public:
	Time(int,int,int);
	int hour;
	int minute;
	int sec;
private:
};

Time::Time(int h,int m,int s)
{
	hour=h;
	minute=m;
	sec=s;
}

void fun(Time&t)//t是Time对象的引用
{
	t.hour=18;
}
int main()
{
	Time t1(10,34,28);
	fun(t1);
	cout<<t1.hour<<endl;
	system("pause");
	return 0;
}


