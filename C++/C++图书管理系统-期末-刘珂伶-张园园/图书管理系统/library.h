#ifndef LIBRARY_H
#define LIBRARY_H
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
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
	void borrow(Teacher_Reader reader, string filename);
	void borrow(Student_Reader reader, string filename);
	void borrow(Outside_campus_Reader reader, string filename);
	void Return(Teacher_Reader reader, string filename);
	void Return(Student_Reader reader, string filename);
	void Return(Outside_campus_Reader reader, string filename);
	void borrowtype(int chiose1);	
	void returntype(int chiose2);
	void checktype();
	template<typename T>
	vector<T> Read(string txtname);
	template<typename T>
	void Write(string txtname,vector<T> info);
	
private:
    static int m_strRCode;
	
};




template<typename T>
vector<T> library::Read(string txtname)
{	
		T b;
		vector<T> info;
		ifstream file(txtname, ios::in);//以读的方式读取文件
		while (!file.eof())//读取txt内容到类数组中，eof判断是否读到文件尾部
		{
			if (!file)
			{
				cout << "BookInventory:文件未正常打开" << endl;
				break;
			}
			file >> b;
			info.push_back(b);
		}
		info.pop_back();//将最后一个重复的元组弹出
		file.close();
		return info;
}

template<typename T>
void library::Write(string txtname,vector<T> info)
{
	ofstream file(txtname, ios::app | ios::out);
	if (!file)
	{
		cout << "文件打开失败" << endl;
	}
	else
	{
		for (unsigned i = 0; i < info.size(); i++)
		{
			file << info[i];
		}

		cout << " 成功保存信息" << endl;
	}
	file.close();
}






#endif