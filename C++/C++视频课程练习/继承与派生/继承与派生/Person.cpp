#include<iostream>
#include"Person.h"
using namespace std;
Person::Person(string name)
{
	m_strName = name;
	cout << "Person()" << endl;
}

Person::~Person()
{
	cout << "~Person()" << endl;
}

void Person::play()
{
	cout << "Person()--play()" << endl;
	cout << m_strName << endl;
}