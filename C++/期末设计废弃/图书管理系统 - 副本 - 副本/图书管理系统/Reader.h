#ifndef _READER_H
#define _READER_H
#include<iostream>
#include<string>
#include<vector>
#include"Book.h"
#include"print.h"

using namespace std;
class Reader:virtual public print,public Book
{
public:
	Reader();
	~Reader();
	string getReaderCode(string code);
	void getName();
	void getBook(Book book);
	void returnBook(Book book);
	string putName();
	string putCode();
	void getCount();
	void AddCount();
	void ReduceCount();
	friend istream& operator>>(istream &is, Reader &reader);
	friend ostream& operator<<(ostream &os, Reader &reader);
	virtual void display();
	vector<Book> readerbook;

protected:
	string m_strName;
	string m_strCode;	
	int UserBookCount;//计算用户的图书本数
};


#endif