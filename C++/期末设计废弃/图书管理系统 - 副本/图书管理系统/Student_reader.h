#ifndef STUDENT_READER_H
#define STUDENT_READER_H
#include"Reader.h"
class Student_reader :virtual public Reader
{
public:
	Student_reader();
	~Student_reader();
	void display();
	friend istream& operator>>(istream &is, Student_reader &student_reader);
	friend ostream& operator<<(ostream &os, Student_reader &student_reader);
private:
	string m_strAcademy;
	string m_strMajor;
	string m_strGrade;

};


istream& operator>>(istream &is, Student_reader &student_reader)
{
	Book book1;
	is >> student_reader.m_strAcademy >> student_reader.m_strMajor >> student_reader.m_strGrade >> student_reader.m_strCode >> student_reader.m_strName >> student_reader.UserBookCount;
	student_reader.readerbook.clear();//不清空会发生意想不到的错误
	for (int i = 0; i < student_reader.UserBookCount; i++)
	{
		is >> book1.m_strBookName >> book1.m_iBookCode >> book1.m_iBookCount;
		student_reader.readerbook.push_back(book1);
	}
	return is;
}




ostream& operator<<(ostream &os, Student_reader &student_reader)
{
	
	os<< student_reader.m_strAcademy << ' ' << student_reader.m_strMajor << ' ' << student_reader.m_strGrade << ' ' << student_reader.m_strCode << ' ' << student_reader.m_strName << ' ' << student_reader.UserBookCount;
	for (unsigned i = 0; i < student_reader.readerbook.size(); i++)
	{
		os << ' ' << student_reader.readerbook[i].m_strBookName << ' ' << student_reader.readerbook[i].m_iBookCode << ' ' << student_reader.readerbook[i].m_iBookCount;
	}
	os << endl;

	return os;
}
void Student_reader::display()
{

	cout << "这是一位学生读者，学生的学院是：" << m_strAcademy << endl;
	cout << "学生的专业是:" << m_strMajor << endl;
	cout << "学生的年级是：" << m_strGrade << endl;
	Reader::display();
}

#endif
