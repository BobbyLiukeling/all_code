#include<iostream>
#include<stdlib.h>
#include<string>
#include"Teacher.h"
using namespace std;

int main(void)
{
	Teacher t1;
	Teacher t2=t1;
	Teacher t3(t2);//F2������F1����
	
	system("pause");
	return 0;
}
