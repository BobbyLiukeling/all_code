#include<iostream>
#include<string>
using namespace std;

class Employee
{
public:
	Employee(int number,string major);
	~Employee();
private:
	int Inumber;
	string Strmajor;
};