#include<iostream>
using namespace std;

//void fun(const int &a,const int &b);//"&"是表示别名,传入的参数是错误的，因为 const不能给常量赋值
void fun( int &a, int &b);

int main()
{
	int x=3;
	int y=5;
	fun(x,y);
	cout<<x<<","<<y<<endl;

	system("pause");
	return 0;
}

//void fun(const int &a,const int &b)
void fun( int &a, int &b)
{
	a=10;
	b=20;
}
