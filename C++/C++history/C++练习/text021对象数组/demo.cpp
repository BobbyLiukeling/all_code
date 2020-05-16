#include<iostream>
#include<stdlib.h>
#include"Coordinate.h"
using namespace std;

int main(void)
{
    Coordinate coor[3];//从栈中定义三个Coordinate
	coor[0].m_ix=3;
	coor[0].m_iy=2;//访问数据成员
	
    Coordinate *p=new Coordinate[3];//申请三个内存块
	p->m_ix=5;//p后不加方括号[]就是现在p所处的位置即p[0]等同于p[0].m_xi=5
	p[0].m_iy=7;
	
	//坐标（1,1）
	p++;//p=p+1
	p->m_ix=11;
	p[0].m_iy=13;

p[1].m_ix=15;
p++;
p->m_iy=18;
	
	for(int i=0;i<3;i++)
	{
		cout<<"coor_x   "<<coor[i].m_ix<<endl;
		cout<<"coor_y   "<<coor[i].m_iy<<endl;
	}

	for(int j=0;j<3;j++)
	{
		cout<<"p_x   "<<p->m_ix<<endl;
		cout<<"p_y   "<<p->m_iy<<endl;
		p--;//p已结在数组的最后位置，所以要减减才能输出
	}

    p++;//让p指回初始位置，在释放p的内存
	delete []p;
	p=NULL;
	
	system("pause");
	return 0;
}