//#define CIRCLE_H

#include"Shape.h"
class Circle:public Shape
{
public:
	Circle(double r);
	~Clircle();
	double caleArea();
protected:
	double m_dR;
};


//#endif 
