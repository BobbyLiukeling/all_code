#include<iostream>
using namespace std;

class Time
{
public:
private:
};

int main()
{
	int *p=new int(20);//直接将20 赋值给P，也可以后面再赋值比如*P=20
	if(p==NULL)
	{
	   system("pause");
	   return 0;
	}
	cout<<*p<<endl;
	delete p;
	p=NULL;


	int *q=new int[10];//申请的是一个有十个整型数的数组空间
	if(q==NULL)
	{
	   system("pause");
	   return 0;
	}
	q[0]=1;
	q[1]=3;
	cout<<q[0]<<","<<q[1]<<endl;
	delete []q;//在释放数组的指针的时候delete后要加“[]”这样才可以释放掉所以申请的数组空间，如果没有就只能释放掉第一个
	q=NULL;
	system("pause");
	return 0;
}
