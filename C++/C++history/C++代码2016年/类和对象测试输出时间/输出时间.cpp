#include<iostream>
using namespace std;
class Time
{
public:
	void set_time(void);
	void show_time(void);
private:
	int hour;
	int minute;
	int sec;
};


Time t;//可以定义为全局变量
int main()
{
	
	t.set_time();
	t.show_time();
	system("pause");
	return 0;
}

void Time::set_time()
{
	cin>>hour>>minute>>sec;
}

void Time::show_time()
{
	cout<<hour<<":"<<minute<<":"<<sec<<endl;
}
