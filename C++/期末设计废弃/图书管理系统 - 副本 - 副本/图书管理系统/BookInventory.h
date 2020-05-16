#ifndef _BOOKINVENTORY_H
#define _BOOKINVENTORY_H
//图书库，将文件内容写入图书数组
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include"Read_Write.h"
using namespace std;

class BookInventory
{
public:
	BookInventory();
	void printBook();
	~BookInventory();
};

#endif