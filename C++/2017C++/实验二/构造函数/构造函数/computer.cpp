#include"computer.h"

Computer::Computer(string model, int price)
{
	Strmodel = model;
	Iprice = price;
	cout << "Computer(string model, int price)" << endl;
}

Computer::~Computer()
{
	cout << "~Computer()" << endl;
}

void Computer::put_name()
{
	cout << "the computer's model is" << Strmodel << endl;
}