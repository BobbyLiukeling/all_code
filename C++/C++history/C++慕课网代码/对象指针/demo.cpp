#include<iostream>
#include<stdlib.h>
#include"Coordinate.h"
using namespace std;

/*
   要求：
       定义Coordinate类
	   数据成员m_ix，m_iy
	   声明对象指针，并通过指针操控对象
	   计算两个点的横、纵坐标的和

 */
int main()
{
	Coordinate *p1=NULL;
	p1=new Coordinate;
	Coordinate *p2=new Coordinate();//与上面代码相比较赋值的结果一样，括号可有可无
	p1->m_iX=10;
	p1->m_iY=20;

	(*p2).m_iX=30;
	(*p2).m_iY=40;
/*两种不同类型的赋值方式*/

	cout<<(p1->m_iX+(*p2).m_iX)<<endl;
	
	cout<p1->m_iY+(*p2).m_iY<<endl

	system("pause");
	return 0;
}