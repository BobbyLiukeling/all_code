#include"Reader.h"

Reader::Reader()
{
	UserBookCount = readerbook.size();
}

Reader::~Reader()
{

}

string Reader::getReaderCode(string code)
{
	m_strCode=code;	
	return m_strCode;
}

void Reader::getName()
{
	cout << "请输入您的名字" << endl;
	string name;
	cin >> name;
	m_strName = name;
}

void Reader::getBook(Book book)
{
	readerbook.push_back(book);
}

void Reader::getCount()
{
	UserBookCount = readerbook.size();
}

void Reader::AddCount()
{
	UserBookCount++;
}

void Reader::ReduceCount()
{
	UserBookCount--;
}

void Reader::display()
{
	cout << "用户ID：" << m_strCode << endl;
	cout << "用户名：" << m_strName << endl;
	for (unsigned i = 0; i < readerbook.size(); i++)
	{
       cout << "借的第 "<<i+1<<" 本书信息:" <<endl;
	   readerbook[i].displayBook();
	}
	UserBookCount = readerbook.size();
	cout << "一共借了 " << UserBookCount << " 本书" << endl;
	cout << endl;
}

string Reader::putName()
{
	return m_strName;
}
string Reader::putCode()
{
	return m_strCode;
}