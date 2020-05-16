#ifndef _BORROWBOOK_H
#define _BORROWBOOK_H
#include<iostream>
#include"Read_Write.h"
#include"Reader.h"
#include"UserType.h"
using namespace std;
class BorrowBook:public Reader
{
public:
	BorrowBook();
	~BorrowBook();
	void borrow();
	void returnBook();
	void TntegrationReader();//将文件内的信息进行整合，每个读者的借书还书信息写到同一个reader类中
	void JudgeReader(Reader& reader1,Reader& reader2);//判断两个reader数据是否为同一个用户
private:
	//int top;
};



#endif