#ifndef _ADDBOOK_H
#define _ADDBOOK_H
//添加图书
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include"Read_Write.h"

using namespace std;

class AddBook :public Book
{
public:
	AddBook();
	virtual ~AddBook();
	void getBook();
private:
	int m_iSum;//记录图书种类数目
};

#endif