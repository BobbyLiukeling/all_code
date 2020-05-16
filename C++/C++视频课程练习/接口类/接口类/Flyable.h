#ifndef _FLYABLE_H
#define _FLYABLE_H

class Flyable
{
public:
	virtual void takeoff() = 0;
	virtual void land() = 0;
};
#endif

