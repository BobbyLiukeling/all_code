#include"cpu.h"

CPU::CPU(string name, int internal)
{
	Strname = name;
	Iinternal = internal;
	cout << "CPU(string name, int internal)" << endl;
}

CPU::~CPU()
{
	cout << "~CPU()" << endl;
}