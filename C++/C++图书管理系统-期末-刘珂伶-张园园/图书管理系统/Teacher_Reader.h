#ifndef  TEACHER_READER_H
#define TEACHER_READER_H
#include"Reader.h"

class Teacher_Reader : public virtual Reader
{
public:
	void display();
	friend istream& operator>>(istream &is, Teacher_Reader &teacher_Reader);
	friend ostream& operator<<(ostream &os, Teacher_Reader &teacher_Reader);
private:
	string m_strProfession;
};


#endif