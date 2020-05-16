#ifndef _BORROWBOOK_H
#define _BORROWBOOK_H
#include<iostream>
#include"Read_Write.h"
#include"Reader.h"
#include"UserType.h"
#include"Outside_campus_Reader.h"
#include"Student_reader.h"
#include"Teacher_Reader.h"

using namespace std;
class BorrowBook:public Reader
{
public:
	BorrowBook();
	~BorrowBook();
	void borrow(int KEY);
	void returnBook(int KEY);
private:
	//int top;
};



#endif