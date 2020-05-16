#ifndef LIBRARY_H
#define LIBRARY_H
#include<iostream>
#include<string>
#include<fstream>
#include"Read_Write.h"
#include"Teacher_Reader.h"
#include"Student_Reader.h"
#include"Outside_campus_Reader.h"
#include"Book.h"
using namespace std;

class library
{
public:
	library();
	~library();
	bool usertype();
	int managelogin();
	void BookInventory();	
	void changeBook();//修改图书信息
	void DropBook();//删除图书信息
	void AddBook();
	int ReaderType();
	int Readerchiose();
	void borrow(Read_Write<Teacher_Reader> userR_W, Read_Write<Teacher_Reader> user, Teacher_Reader reader, string filename);
	void borrow(Read_Write<Student_Reader> userR_W, Read_Write<Student_Reader> user, Student_Reader reader, string filename);
	void borrow(Read_Write<Outside_campus_Reader> userR_W, Read_Write<Outside_campus_Reader> user, Outside_campus_Reader reader, string filename);
	void Return(Read_Write<Teacher_Reader> returnR_W, Teacher_Reader reader, string filename);
	void Return(Read_Write<Student_Reader> returnR_W, Student_Reader reader, string filename);
	void Return(Read_Write<Outside_campus_Reader> returnR_W, Outside_campus_Reader reader, string filename);
	void borrowtype(int chiose1);	
	void returntype(int chiose2);
	void checktype();
	
private:
    static int m_strRCode;
	
};

#endif