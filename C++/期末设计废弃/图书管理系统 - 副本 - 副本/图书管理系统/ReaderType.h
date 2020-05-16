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
	void Readertype();
	void readerchiose(int ReaderChiose);
	static int key;
};

int ReaderType::key = 1;

void ReaderType::Readertype()
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

}

void ReaderType::readerchiose(int ReaderChiose)
{
	switch (key)//选择用户
	{
	case 1:
	{
		BorrowBook<Teacher_Reader> Bor;
		Bor.getfilename("Teacher_Reader.txt");

		while (true)
		{
			switch (ReaderChiose)
			{

			case 1://查询图书
			{
				BookInventory B;
				B.printBook();//查询
				break;
			}
			case 2://借书
			{
				Bor.borrow();
				break;
			}
			case 3://还书
			{
				Bor.returnBook();
				break;
			}
			default:
				break;
			}
			string key;
			cout << "是否继续操作，是请按1，否请按任意键退出" << endl;
			cin >> key;
			if (key == "1")
			{
				continue;
			}
			else
			{
				break;
			}
		}
		break;
	}
	case 2:
	{
		BorrowBook<Student_reader> Bor;
		Bor.getfilename("Student_reader.txt");
		while (true)
		{
			switch (ReaderChiose)
			{

			case 1://查询图书
			{
				BookInventory B;
				B.printBook();//查询
				break;
			}
			case 2://借书
			{
				Bor.borrow();
				break;
			}
			case 3://还书
			{
				Bor.returnBook();
				break;
			}
			default:
				break;
			}
			string key;
			cout << "是否继续操作，是请按1，否请按任意键退出" << endl;
			cin >> key;
			if (key == "1")
			{
				continue;
			}
			else
			{
				break;
			}
		}
		break;
	}
	case 3:
	{
		BorrowBook<Outside_campus_Reader>  Bor;
		Bor.getfilename("Outside_campus_Reader.txt");
		while (true)
		{
			switch (ReaderChiose)
			{

			case 1://查询图书
			{
				BookInventory B;
				B.printBook();//查询
				break;
			}
			case 2://借书
			{
				Bor.borrow();
				break;
			}
			case 3://还书
			{
				Bor.returnBook();
				break;
			}
			default:
				break;
			}
			string key;
			cout << "是否继续操作，是请按1，否请按任意键退出" << endl;
			cin >> key;
			if (key == "1")
			{
				continue;
			}
			else
			{
				break;
			}
		}
		break;
	}
	default:
		break;
	}

}



#endif