#include"Circle.h"

Circle::caleArea(double r)
{
	m_dR=r;
	cout<<"Circle()"<<endl;
}

Circle::~Circle()
{
	cout<<"~Circle()"<<endl;
}

double Circle::caleArea()
{
	cout<<"Circle->caleArea()"<<endl;
	return m_dR*m_dR*3.14;
}