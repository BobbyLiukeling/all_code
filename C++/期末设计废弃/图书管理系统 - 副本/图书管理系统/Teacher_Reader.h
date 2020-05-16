#ifndef  TEACHER_READER_H
#define TEACHER_READER_H
#include"Reader.h"

class Teacher_Reader:virtual public Reader
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
	Book book1;
	is >> teacher_Reader.m_strProfession>> teacher_Reader.m_strCode >> teacher_Reader.m_strName >> teacher_Reader.UserBookCount;
	teacher_Reader.readerbook.clear();//不清空会发生意想不到的错误
	for (int i = 0; i < teacher_Reader.UserBookCount; i++)
	{
		is >> book1.m_strBookName >> book1.m_iBookCode >> book1.m_iBookCount;
		teacher_Reader.readerbook.push_back(book1);
	}
	return is;
}


ostream& operator<<(ostream &os, Teacher_Reader &teacher_Reader)
{
	os << teacher_Reader.m_strProfession << ' '<< teacher_Reader.m_strCode << ' ' << teacher_Reader.m_strName << ' ' << teacher_Reader.UserBookCount;
	for (unsigned i = 0; i < teacher_Reader.readerbook.size(); i++)
	{
		os << ' ' << teacher_Reader.readerbook[i].m_strBookName << ' ' << teacher_Reader.readerbook[i].m_iBookCode << ' ' << teacher_Reader.readerbook[i].m_iBookCount;
	}
	os << endl;
	return os;
}
void Teacher_Reader::display()
{

	cout << "这是一位老师读者，老师的专业是：" << m_strBookName << endl;
	Reader::display();
}



#endif