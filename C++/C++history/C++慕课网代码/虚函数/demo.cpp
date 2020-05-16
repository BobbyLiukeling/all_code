#include<iostream>
#include<stdlib.h>
#include"Rect.h"
#include"Circle.h"
using namespace std;

/*动态多态：虚函数
      要求：
	       1、定义Shape类，成员函数：calcArea（），构造函数，析构函数
		   2、定义Rect类，成员函数：caclArea（），构造函数，析构函数
		                  数据成员：m_dWidth，m_dHeight
           3、定义Circle类 成员函数caclArea（），构造函数，析构函数
		                   数据成员：m_dR
*/

int main()
{
	Shape *shape1=new Rect(3.6);
	Shape *shape2=new Circle(5);
	
	shape1->caleArea();
	shape2->caleArea();

	delete shape1;
	delete shape2;


	system("pause");
	return 0;
		 
}