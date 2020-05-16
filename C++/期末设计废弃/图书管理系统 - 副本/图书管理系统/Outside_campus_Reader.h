#ifndef OUTSUDE_CAMPUS_READER_H
#define OUTSUDE_CAMPUS_READER_H
#include"Reader.h"


class Outside_campus_Reader :virtual public Reader
{
public:
	Outside_campus_Reader();
	~Outside_campus_Reader();
	void display();
	friend istream& operator>>(istream &is, Outside_campus_Reader &outside_campus_Reader);
	friend ostream& operator<<(ostream &os, Outside_campus_Reader &outside_campus_Reader);
private:
	string m_strAdress;
	string m_strTelephoneNumber;
};

void Outside_campus_Reader::display()
{
	cout << "这是一位校外读者，读者的住址是：" << m_strAdress << endl;
	cout << "读者的电话号码是：" << m_strTelephoneNumber << endl;
	Reader::display();
}



istream& operator>>(istream &is, Outside_campus_Reader &outside_campus_Reader)
{
	Book book1;
	is>> outside_campus_Reader.m_strAdress >> outside_campus_Reader.m_strTelephoneNumber >> outside_campus_Reader.m_strCode >> outside_campus_Reader.m_strName >> outside_campus_Reader.UserBookCount;
	outside_campus_Reader.readerbook.clear();//不清空会发生意想不到的错误
	for (int i = 0; i < outside_campus_Reader.UserBookCount; i++)
	{
		is >> book1.m_strBookName >> book1.m_iBookCode >> book1.m_iBookCount;
		outside_campus_Reader.readerbook.push_back(book1);
	}
	return is;
}
ostream& operator<<(ostream &os, Outside_campus_Reader &outside_campus_Reader)
{
	os<< outside_campus_Reader.m_strAdress << ' ' << outside_campus_Reader.m_strTelephoneNumber << ' ' << outside_campus_Reader.m_strCode << ' ' << outside_campus_Reader.m_strName << ' ' << outside_campus_Reader.UserBookCount;
	for (unsigned i = 0; i < outside_campus_Reader.readerbook.size(); i++)
	{
		os << ' ' << outside_campus_Reader.readerbook[i].m_strBookName << ' ' << outside_campus_Reader.readerbook[i].m_iBookCode << ' ' << outside_campus_Reader.readerbook[i].m_iBookCount;
	}
	os << endl;
	return os;
}


#endif