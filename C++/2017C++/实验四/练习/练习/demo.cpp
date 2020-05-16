#include <iostream>
#include"Array.h"
using namespace std;
int main()
{
	Array arr1(5);
	Array arr2(arr1);

	arr1.print1();
	arr2.print1();

	cout << "lalalal " << endl;
	getchar();
	return 0;
}