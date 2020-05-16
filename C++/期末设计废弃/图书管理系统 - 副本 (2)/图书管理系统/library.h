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
	template<class R>
	void borrow(Read_Write<R> userR_W, Read_Write<R> user,R reader,string filename);
	template<class T>
	void Return(Read_Write<T> returnR_W, T reader, string filename);
	void borrowtype(int chiose);	
	void returntype(int chiose);
	void checktype();
private:
    static string m_strRCode;
};

template<class R>
void library::borrow(Read_Write<R> userR_W, Read_Write<R> user, R reader, string filename)
{
	//1、输入用户信息
	//2、输入要借的图书信息，并从文件中读出查找显示
	//3、选择要借的图书
	//4、将已经借了的图书信息更新到用户文件
	//5、更新图书文件

	reader.getReaderCode(library::m_strRCode);//将用户ID传入
	ifstream file(filename);
	bool key3 = false;//用于验证

	//Reader文件存在判断是否此用户是否已经存在，如果存在，将信息提取出来并在Reader.txt中删除此用户信息，以便更新
	if (file)
	{
		user.ToRead(filename);
		for (unsigned i = 0; i < user.info.size(); i++)
		{
			if (user.info[i].putCode() == reader.putCode())//已经有借书记录的用户
			{
				userR_W.info.push_back(user.info[i]);//将此用户信息提取出来
				if ((user.info.begin() + i) != user.info.end())//再将此用户信息弹出，以便之后更新不会重复
				{
					user.info.erase(user.info.begin() + i);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
				}
				else
				{
					user.info.pop_back();//如果要删除的是最后一个元组的话
				}
				key3 = true;//老用户
				ofstream file1(filename, ios::trunc | ios::out);//将文件清空以便重新写入
				file1.close();
				user.ToWrite(filename);//再写入文件
			}
		}
	}
	if (key3 == false)
	{
		reader.getName();//新用户，输入姓名
	}
	Read_Write<Book> read;//read是info类型			
	int a = 0;
	Book *p = new Book[read.info.size()];//用于接收借书后要修改的图书信息
	Book *t = p;//t将用于对p 的重置
	string key2;//用于判断是否查找出需要借的图书，并对借书后的文件进行修改
	while (true)//找出需要借的图书
	{
		read.ToRead("book.txt");//每次循环重新读取info信息
		system("cls");
		p = t;//新一轮借书是重置P，
		cout << "········请输入你要借的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.info.size(); i++)//打印从txt中读取的结果
		{
			if ((read.info[i].m_strBookName.find(key) != string::npos) || (read.info[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read.info[i].displayBook();
				cout << endl;
				p = &(read.info[i]);
				p++;
			}
		}
		if (a == 0)//未规范输入判断
		{
			cout << "没有您要借图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;

			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了借书" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出借书
	{
		int t;
		if (a == 1)
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要借的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		for (unsigned i = 0; i < read.info.size(); i++)//嵌套太多，待优化
		{
			if (&(p[t - a - 1]) == &(read.info[i]))//先找到相同地址
			{
				if (read.info[i].m_iBookCount < 0 || read.info[i].m_iBookCount == 0)//再判断书数量为0，不可借
				{
					cout << "此书不可借" << endl;
					break;
				}
				else
				{
					read.info[i].m_iBookCount--;//还要找到地址，将文件进行修改
					reader.AddCount();
					reader.readerbook.push_back(read.info[i]);//将借书信息写入用户信息
					//将用户信息写入文件
					reader.getCount();
					if (key3)//此用户之前已经借过书
					{
						//userR_W.info.之前已经user.info[i]被实例化了,且userR_W.info只有一个元组
						userR_W.info[0].readerbook.insert(userR_W.info[0].readerbook.end(), reader.readerbook.begin(), reader.readerbook.end());
					}
					else//此用户之前未借过书
					{
						userR_W.info.push_back(reader);
					}
					userR_W.ToWrite(filename);//追加到Reader.txt 文件中
					break;
				}
			}
		}
		cout << "借书结束" << endl;
		break;

	}//外层while结束

	//借书完成将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	read.ToWrite("book.txt");
}

template<class T>
void library::Return(Read_Write<T> returnR_W, T reader, string filename)
{
	//1、读取读者信息（不显示）
	//2、匹配用户名或ID
	//3、显示借书信息
	//4、选择要还图书
	//5、修改读者信息
	//6、修改文件信息
	returnR_W.ToRead(filename);//1、读取读者信息（不显示）
	while (true)
	{
		string key1, name;
		key1 = reader.getReaderCode(library::m_strRCode);//将用户ID传入		
		string key4;//判断是否继续还书vector<int>key7;//记录用户在vector流中的位置
		int key5;
		bool key2 = false;//判断用户是否存在
		for (unsigned i = 0; i < returnR_W.info.size(); i++)
		{
			if (returnR_W.info[i].putCode() == key1)//找到用户
			{
				key2 = true;
				reader = returnR_W.info[i];
				//cout << "查询出的第 " << reader.size() << " 位用户" << endl;
				key5 = i;//记录用户在vector流中的位置
				returnR_W.info[i].display();//输出用户信息
			}
		}

		//不存在此用户
		if (key2 == false)
		{
			cout << "此用户不存在" << endl;
			break;
		}
		if (reader.readerbook.size() < 1)
		{
			cout << "您还未借书" << endl;
			break;
		}

		//此用户存在
		else
		{
			cout << "请输入要归还的图书序号" << endl;
			int key3;
			cin >> key3;

			//将修改的信息写入Book.txt  和  ReaderInfo.txt
			Read_Write<Book> bookR_W;
			bookR_W.ToRead("book.txt");
			for (unsigned i = 0; i < bookR_W.info.size(); i++)
			{
				if (reader.readerbook[key3].m_strBookName == bookR_W.info[i].m_strBookName && reader.readerbook[key3].m_iBookCode == bookR_W.info[i].m_iBookCode)//在book.txt 中找到用户还的那本书
				{
					bookR_W.info[i].m_iBookCount++;
				}
			}

			if ((reader.readerbook.begin() + key3 - 1) != reader.readerbook.end())
			{
				reader.readerbook.erase(reader.readerbook.begin() + key3 - 1);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				reader.readerbook.pop_back();//如果要删除的是最后一个元组的话
			}
			reader.ReduceCount();//用户的借书总量减少一本

			ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
			file1.close();
			bookR_W.ToWrite("book.txt");//写入book.txt文件

			//将reader即修改后的单个用户信息更新流中相应的用户信息
			returnR_W.info.insert(returnR_W.info.begin() + key5, reader);//在流的指定位置插入数据
			//将修改的信息写入ReaderInfo.txt
			ofstream file2(filename, ios::trunc | ios::out);//将文件清空以便重新写入
			file2.close();
			returnR_W.ToWrite(filename);//写入文件				

			cout << "是否继续归还,是请按1，否则按任意键退出" << endl;
			cin >> key4;
			if (key4 == "1" && reader.readerbook.size() > 0)//当此用户还有书，且确认继续归还时
				continue;
			else
			{
				cout << "还书成功" << endl;
				break;//退出内层while
			}
		}
		if (key4 != "1")
		{
			break;//退出外层while
		}
	}
}

void library::borrowtype(int chiose)
{
	switch (chiose)
	{
	case 1:
	{
		Read_Write<Teacher_Reader> userR_W;
		Read_Write<Teacher_Reader> user;
		Teacher_Reader reader;
		borrow(userR_W, user, reader, "Teacher_Reader.txt");
		break;
	}
	case 2:
	{
		Read_Write<Student_Reader> userR_W;
		Read_Write<Student_Reader> user;
		Student_Reader reader;
		borrow(userR_W, user, reader, "Student_Reader.txt");
		break;
	}
	case 3:
	{
		Read_Write<Outside_campus_Reader> userR_W;
		Read_Write<Outside_campus_Reader> user;
		Outside_campus_Reader reader;
		borrow(userR_W, user, reader, "Outside_campus_Reader.txt");
		break;
	}	
	default:
		break;
	}
}

void library::returntype(int chiose)
{
	switch (chiose)
	{
	case 1:
	{
		Read_Write<Teacher_Reader> returnR_W;
		Teacher_Reader reader;
		Return(returnR_W,reader, "Teacher_Reader.txt");
		break;
	}
	case 2:
	{
		Read_Write<Student_Reader> returnR_W;
		Student_Reader reader;
		Return(returnR_W, reader, "Student_Reader.txt");
		break;
	}
	case 3:
	{
		Read_Write<Outside_campus_Reader> returnR_W;
		Outside_campus_Reader reader;
		Return(returnR_W,  reader, "Outside_campus_Reader.txt");
		break;
	}
	default:
		break;
	}
}




#endif