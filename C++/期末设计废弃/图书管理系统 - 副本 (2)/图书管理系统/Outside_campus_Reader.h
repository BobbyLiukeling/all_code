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

#endif