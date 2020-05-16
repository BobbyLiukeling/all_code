#ifndef BODY_H_
#define BODY_H_

#include<iostream>
#include<string>
using namespace std;

//掌握对象的调用方法，理解并熟练使用友元，掌握运算符重载的方法
//编写程序，定义body类，记录班上学生的身体健康状况，要求：
//①需使用对象数组；
//②body类的数据成员参考体检项目；
//③body类的函数成员除输入和输出外，应有健康状况的评价。
class body
{
public:
	body();
	body(char name,int height,int weight);
	void getbody();
	friend void cheakbody(body&);
	~body();
private:
	string Strname;
	int Iheight;
	int Iweight;
};

#endif