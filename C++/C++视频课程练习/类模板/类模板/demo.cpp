#include<iostream>
#include"MyArray.h"

using namespace std;

int main()
{
	MyArray<int, 5, 3> arr;
	arr.display();
	getchar();
	return 0;
}