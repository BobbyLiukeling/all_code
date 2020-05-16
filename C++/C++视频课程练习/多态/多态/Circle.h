#ifndef _CIRCLE_H
#define _CIRCLE_H

#include"Shape.h"

class Circle:public Shape
{
public:
	Circle(double r);
	~Circle();
	double calcArea();
private:
	double m_dR;
};


#endif