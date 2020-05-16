#ifndef _RECT_H
#define _RECT_H

#include"Shape.h"
class Rect:public Shape
{
public:
	Rect(double width,double heigth);
	~Rect();
	double calcArea();
private:
	double m_dWidth;
	double m_dHeight;
};

#endif