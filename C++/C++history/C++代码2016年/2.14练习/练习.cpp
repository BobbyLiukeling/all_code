#include<iostream>
using namespace std;

class Date
{
public:
	Date(int,int,int);
	Date(int,int);
	Date(int);
	Date();
	void display();
private:
	int month;
	int day;
	int year;
};

Date::Date(int m,int d,int y):month(m),day(d),year(y){}

Date::Date(int m,int d):month(m),day(d)
{
	year=2009;
}

Date::Date(int m):month(m)
{
	day=1;
	year=2009;
}

Date::Date():month(2),day(13),year(2016)
{
	month=1;
	day=1;
	year=1;
}

void Date::display()
{
	cout<<month<<"/"<<day<<"/"<<year<<endl;
}
int main()
{
	Date d1(10,23,2005);
	Date d2(10,23);
	Date d3(10);
	Date d4();
	d1.display();
	d2.display();
	d3.display();
	d4.display();
	system("pause");
	return 0;
}
