#include<iostream>
#include"Person.h"

Person::Person()
{
	cout << "Person()" << endl;
}

Person::~Person()
{
	cout << "~Person()" << endl;
}

void Person::eat()
{
	m_strName = "Jim";
	m_iAge = 20;
	cout << "eat()" << endl;
}