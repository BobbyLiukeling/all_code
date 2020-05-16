#include<iostream>//友元函数可以可也不是类的成员，但访问类重成员，就像是客人允许进入家里的房间一样
using namespace std;

class Time
{
public:
	Time(int,int,int);
	friend void display(Time&);//声明display为友元函数
private:
	int hour;
	int minute;
	int sec;
};

Time::Time(int h,int m,int s)
{
	hour=h;
	minute=m;
	sec=s;
}

void display(Time&t)
{
    cout<<t.hour<<":"<<t.minute<<":"<<t.sec<<endl;
}
int main()
{
	Time t1(12,45,37);
	display(t1);
	system("pause") ;
	return 0;
}
