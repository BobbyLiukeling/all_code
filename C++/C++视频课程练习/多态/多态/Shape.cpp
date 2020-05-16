#include<iostream>
#include"Shape.h"
using namespace std;

Shape::Shape()
{
	cout <<"Shape()" << endl;
}

Shape::~Shape()
{
	cout << "~Shape()" << endl;
}

double Shape::calcArea()
{	
	cout << "Shape::calcArea()" << endl;
	return 0;
}
