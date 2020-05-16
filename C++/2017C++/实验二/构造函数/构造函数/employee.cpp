#include"employee.h"

Employee::Employee(int number, string major)
{
	Inumber = number;
	Strmajor = major;
	cout << "Employee(int number, string major)" << endl;
}

Employee::~Employee()
{
	cout << "~Employee()" << endl;
}