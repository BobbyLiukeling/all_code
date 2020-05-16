#include<iostream>
#include"Soldier.h"

using namespace std;

int main()
{
	Person *p=new Soldier;
	p->play();
	delete p;
	p = NULL;

	getchar();
	return 0;
}