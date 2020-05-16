#ifndef CHECKREADER_H
#define CHECKREADER_H
#include"Outside_campus_Reader.h"
#include"Student_reader.h"
#include"Teacher_Reader.h"
#include"Read_Write.h"

using namespace std;

class CheckReader
{
public:
	CheckReader();
	~CheckReader();
	void checktype();
private:

};


void CheckReader::checktype()
{
	cout << "请选择要查看的读者类型：" << endl;
	cout << "1、教职工读者用户" << endl;
	cout << "2、学生读者用户" << endl;
	cout << "3、校外读者用户" << endl;
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
	{
		Read_Write<Teacher_Reader>ReaderUser;
		ReaderUser.ToRead("Teacher_Reader.txt");
		for (unsigned i = 0; i < ReaderUser.book.size(); i++)
		{
			ReaderUser.book[i].display();
		}
		break;
	}
	case 2:
	{
		Read_Write<Student_reader>ReaderUser;
		ReaderUser.ToRead("Student_reader.txt");
		for (unsigned i = 0; i < ReaderUser.book.size(); i++)
		{
			ReaderUser.book[i].display();
		}
		break;
	}
	case  3:
	{
		Read_Write<Outside_campus_Reader>ReaderUser;
		ReaderUser.ToRead("Outside_campus_Reader.txt");
		for (unsigned i = 0; i < ReaderUser.book.size(); i++)
		{
			ReaderUser.book[i].display();
		}
		break;
	}
	default:
	{
		cout << "请正确选择，无此类型用户，查询失败" << endl;
		break;
	}
		
	}
}
CheckReader::CheckReader()
{
}

CheckReader::~CheckReader()
{
}

#endif