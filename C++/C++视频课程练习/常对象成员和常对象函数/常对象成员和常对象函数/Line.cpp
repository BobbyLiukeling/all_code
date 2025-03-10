#include<iostream>
#include"Coordinate.h"
#include"Line.h"

using namespace std;

Line::Line(int x1, int y1, int x2, int y2)
{
	m_coorA = new Coordinate(x1, y1);

	cout << "Line()" << endl;
}

Line::~Line()
{
	delete m_coorA;
	m_coorA = NULL;
	delete m_coorB;
	m_coorB = NULL;
	cout << "~Line()" << endl;
}

void Line::printInfo()
{
	cout << "printInfo()" << endl;
	cout << "(" << m_coorA->getX() << "," << m_coorA->getY() << ")" << endl;
	cout << "(" << m_coorB->getX() << "," << m_coorB->getY() << ")" << endl;
}