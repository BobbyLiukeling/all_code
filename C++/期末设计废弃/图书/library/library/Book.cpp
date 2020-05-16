#include<iostream>
#include"Book.h"
using namespace std;
//图书信息
Book::Book()
{
	m_strBookName = "C++";
	m_iBookCode = "001";
	m_iBookCount = 2;
}

Book::Book(string book_name, string book_code, int book_count)
{
	m_strBookName = book_name;
	m_iBookCode = book_code;
	m_iBookCount = book_count;
}

Book::~Book()
{
}

istream& operator>>(istream &is, Book &book)//read
{
	is >> book.m_strBookName >> book.m_iBookCount >> book.m_iBookCode;
	return is;
}

ostream& operator<<(ostream &os, Book &book)//write
{
	os << book.m_strBookName << ' ' << book.m_iBookCount << ' ' << book.m_iBookCode << endl;
	return os;
}

void Book::displayBook()
{
	cout << "图书名称：" << m_strBookName << endl;
	cout << "图书编号：" << m_iBookCode << endl;
	cout << "此书剩余：" << m_iBookCount << " 本" << endl;
	cout << endl;
}