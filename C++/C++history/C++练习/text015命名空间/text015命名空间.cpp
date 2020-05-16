#include<iostream>
using namespace std;
namespace A
{
	int x=1;
	void fun(void)
	{
		cout<<"A"<<endl;
	}
}
namespace B
{
	int x=2;
	void fun(void)
	{
		cout<<"B"<<endl;
	}
}
void main()
{
	cout<<A::x<<endl;
	B::fun();
}