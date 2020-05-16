#ifndef _PLANE_H
#define _PLANE_H

#include"string.h"
#include"Flyable.h"

class Plane:public Flyable
{
public:
	Plane(string code);
	virtual void takeoff();
	virtual void land();
	void printCode();
private:
	string m_strCode;
};

#endif