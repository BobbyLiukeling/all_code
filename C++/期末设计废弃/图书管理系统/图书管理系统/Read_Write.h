#ifndef _READTXT_H
#define _READTXT_H
#include<iostream>
#include<vector>
#include<fstream>
#include"Book.h"
using namespace std;

template<class T>
class Read_Write//将文件内容读到book数组中
{
public:
	Read_Write();
	~Read_Write();
	void ToWrite(string txtname);
	void ToRead(string txtname);
	void getBook(T t);
	vector<T> book;
};
template<class T>
Read_Write<T>::Read_Write()
{

}
template<class T>
void Read_Write<T>::getBook(T t)
{
	book.push_back(t);
}
template<class T>
void Read_Write<T>::ToRead(string txtname)
{
	T b;
	ifstream file(txtname, ios::in);//以读的方式读取文件
	while (!file.eof())//读取txt内容到类数组中，eof判断是否读到文件尾部
	{
		if (!file)
		{
			cout << "BookInventory:文件未正常打开" << endl;
			break;
		}
		file >> b;
		book.push_back(b);
	}
	book.pop_back();//将最后一个重复的元组弹出
	file.close();
}
template<class T>

void Read_Write<T>::ToWrite(string txtname)//将内容以追加的方式读入txt
{
	ofstream file(txtname, ios::app | ios::out);
	if (!file)
	{
		cout << "文件打开失败" << endl;
	}
	else
	{
		for (unsigned i = 0; i < book.size(); i++)
		{
			file << book[i];  
		}
		
		 cout<<" 成功保存信息" << endl;
	}

	file.close();
}
template<class T>
Read_Write<T>::~Read_Write()
{
}

#endif