#include<iostream>
#include"Coordinate.h"

using namespace std;

Coordinate::Coordinate(int x, int y)
{
	m_iY = y;
	m_iX = x;
	cout << "Coordinate()" << m_iX << "  " << m_iY << endl;
}

Coordinate::~Coordinate()
{
	cout << "~Coordinate" << m_iX << "  " << m_iY << endl;
}

int Coordinate::getX()
{
	return m_iX;
}

int Coordinate::getY()
{
	return m_iY;
}