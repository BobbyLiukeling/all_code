#include<iostream>
#include<stdlib.h>
#include"Array.h"
using namespace std;

int main(void)
{
	Array arr1(5);

	Array arr2(arr1);

	arr1.printAddr();
	arr2.printAddr();

	system("pause");
}