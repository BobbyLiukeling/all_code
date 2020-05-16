#include<iostream>
#include<stdlib.h>
using namespace std;

class Coordinate
{
public:
	int x;
	int y;
	void printx()
	{
		cout<<x<<endl;
	}
	void printy()
	{
		cout<<y<<endl;
	}
};

int main(void)
{
    Coordinate Coor;
	Coor.x=10;
	Coor.y=20;
	Coor.printx();
	Coor.printy();


	Coordinate *p=new Coordinate();
	if(NULL==p)
	{
		return 0;//读取内存失败，退出
	}
	p->x =100;
	p->y =200;
	p->printx();
	p->printy();

	delete p;//释放内存
	p=NULL;//释放p

	system("pause");
	return 0;
}
