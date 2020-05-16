#include<iostream>
#include"Array.h"

using namespace std;

int main()
{
	Array arr1(10);
	arr1.printinfo().setLen(5);
	cout << "len=" << arr1.getLen() << endl;

	getchar();
	return 0;
}