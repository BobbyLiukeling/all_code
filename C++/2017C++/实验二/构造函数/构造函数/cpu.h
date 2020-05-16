#include<iostream>
#include<string>
using namespace std;

class CPU
{
public:
	CPU(string name,int internal);
	~CPU();
private:
	string Strname;
	int Iinternal;	
};
