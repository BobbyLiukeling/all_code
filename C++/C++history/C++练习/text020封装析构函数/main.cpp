#include<iostream>
#include<stdlib.h>
#include<string>
#include"Teacher.h"
using namespace std;

int main(void)//析构函数就是在普通函数前加上 ~ 就可以，其作用是在程序运算完成后用来释放内存的
{
	Teacher t1;
	//Teacher t2=t1;
	//Teacher t3(t2);//F2可以用F1代替
	
	cin.get();
	return 0;
}
