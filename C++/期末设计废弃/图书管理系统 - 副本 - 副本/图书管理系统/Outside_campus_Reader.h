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
	is >> outside_campus_Reader.m_strAdress >> outside_campus_Reader.m_strTelephoneNumber;
	istream& operator>>(istream &is, Reader &reader);
	return is;
}
ostream& operator<<(ostream &os, Outside_campus_Reader &outside_campus_Reader)
{
	os << outside_campus_Reader.m_strAdress << ' ' << outside_campus_Reader.m_strTelephoneNumber<< ' ' ;
	istream& operator<<(istream &os, Reader &reader);
	return os;
}


#endif