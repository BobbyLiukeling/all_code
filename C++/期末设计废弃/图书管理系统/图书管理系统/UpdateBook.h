#ifndef _UPDATEBOOK_H
#define _UPDATEBOOK_H

#include"BookInventory.h"
#include"Read_Write.h"
class UpdateBook:public Book
{
public:
	UpdateBook();
	~UpdateBook();
	void changeBook();//修改图书信息
	void DropBook();//删除图书信息
private:
	int top;//用于标记将要被删除的那本书
};



#endif 