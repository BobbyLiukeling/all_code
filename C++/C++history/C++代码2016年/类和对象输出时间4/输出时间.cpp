#include<iostream>
using namespace std;

class Time
{
public:
	int hour;
	int minute;
	int sec;
};

int main()
{
	void set_time(Time&,int hour=0,int minute=0,int sec=0);
	void show_time(Time&);

	Time t1;
	set_time(t1,12,23,34);
	show_time(t1);
	Time t2;
	set_time(t2);
	show_time(t2);
	system("pause");
    return 0;
}

void set_time(Time&t,int hour,int minute,int sec)
{
	cin>>t.hour;
	cin>>t.minute;
	cin>>t.sec;
}

void show_time(Time&t)
{
	cout<<t.hour<<":"<<t.minute<<":"<<t.sec<<endl;
}
