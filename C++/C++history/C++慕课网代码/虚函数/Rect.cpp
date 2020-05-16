#include"Rect.h"

Rect::Rect(double width,double height)
{
	cout<<"Rect"<<endl;
	m_dWidth=width;
	m_dHeigth=heigth;
}

Rect::~Rect()
{
	cout<<"~Rect()"<<endl;
}

Rect::caleArea()
{
	cout<<"Retc->caleArea()"<<endl;
	return m_dWidth*m_dHeight;
}
