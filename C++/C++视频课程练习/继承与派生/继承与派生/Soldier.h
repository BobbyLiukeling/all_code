#include"Person.h"

class Soldier:public Person
{
public:
	Soldier(string name="James",int age=20);
	virtual~Soldier();
	void work();
private:
	int m_iAge;
};

