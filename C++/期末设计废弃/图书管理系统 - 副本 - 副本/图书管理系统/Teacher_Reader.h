#ifndef  TEACHER_READER_H
#define TEACHER_READER_H
#include"Reader.h"

class Teacher_Reader :virtual public Reader
{
public:
	Teacher_Reader();
	~Teacher_Reader();
	void display();
	friend istream& operator>>(istream &is, Teacher_Reader &Teacher_Reader);
	friend ostream& operator<<(ostream &os, Teacher_Reader &Teacher_Reader);
private:
	string m_strProfession;
};


istream& operator>>(istream &is, Teacher_Reader &teacher_Reader)
{
	is >> teacher_Reader.m_strProfession;
	istream& operator>>(istream &is, Reader &reader);
	return is;
}
ostream& operator<<(ostream &os, Teacher_Reader &teacher_Reader)
{
	os << teacher_Reader.m_strProfession << ' ';
	istream& operator<<(istream &os, Reader &reader);
	return os;
}
void Teacher_Reader::display()
{

	cout << "这是一位老师读者，老师的专业是：" << m_strBookName << endl;
	Reader::display();
}



#endif