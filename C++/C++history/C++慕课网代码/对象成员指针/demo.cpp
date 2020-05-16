#include<iostream>
#include<stdlib.h>
#include"Line.h"

using namespace std;

/*  对象成员指针
       
		 定义两个类
		     坐标类：Coordinate   数据成员m_iY，m_iX    ，构造函数，析构函数，数据封装函数
			 线段类：Line         数据成员点指针A：m_pCoorA，点指针B：m_pCoorB。
*/


int main()
{
	Line *p=new Line(1,2,3,4);
	p->printInfo();
	delete p;

	cout<<sizeof(p)<<endl;
	cout<<sizeof(Line)<<endl;//line类中申请了两个指针所以占8个内存单元
	system("pause");
	return 0;
}
