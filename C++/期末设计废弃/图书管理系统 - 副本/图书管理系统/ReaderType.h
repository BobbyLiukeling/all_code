#ifndef READERTYPE_H
#define READERTYPE_H
#include"Outside_campus_Reader.h"
#include"Student_reader.h"
#include"Teacher_Reader.h"
#include"BorrowBook.h"
#include"BookInventory.h"

using namespace std;

class ReaderType
{
public:
	ReaderType();
	~ReaderType();
	int Readertype();
private:
	int key;
};

int ReaderType::Readertype()
{
	cout << "请选择读者类型：" << endl;
	cout << "1、教职工读者用户" << endl;
	cout << "2、学生读者用户" << endl;
	cout << "3、校外读者用户" << endl;
	int key1;
	while (1)//选择读者用户类型
	{
		cin >> key1;
		if (key1 == 1 || key1 == 2 || key1 == 3)
		{
			break;
			key = key1;
		}
		else
		{
			cout << "输入不正确" << endl;
			cout << "重新输入请按1，否则按任意键退出" << endl;
			string key2;
			cin >> key2;
			if (key2 == "1")
			{
				continue;
			}
			else
			{
				break;
				key = 0;
			}
		}
	}
	return key;

}


#endif