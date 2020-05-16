#ifndef _FIGHTPLANE_H
#define _FIGHTPLANE_H

#include"string.h"
#include"Plane.h"

class FightPlane :public Plane
{
public:
	FightPlane(string code) :Plane(code){}
	virtual void takeoff();
	virtual void land();
};

#endif