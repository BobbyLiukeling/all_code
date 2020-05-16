#include<iostream>
#include"Rect.h"

using namespace std;
Rect::Rect(double width,double height)
{
	m_dHeight = height;
	m_dWidth = width;
	cout << "Rect()" << endl;
}

Rect::~Rect()
{
	cout << "~Rect()" << endl;
}

double Rect::calcArea()
{
	cout << "Rect::calcArea()" << endl;
	return m_dHeight*m_dWidth;
}