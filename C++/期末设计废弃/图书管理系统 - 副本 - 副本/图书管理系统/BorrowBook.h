#ifndef _BORROWBOOK_H
#define _BORROWBOOK_H
#include<iostream>
#include"Read_Write.h"
#include"Reader.h"
#include"UserType.h"
#include"ReaderType.h"
using namespace std;

template<typename R>
class BorrowBook:public Reader
{
public:
	BorrowBook();
	~BorrowBook();
	void borrow();
	void returnBook();
	void getfilename(string filereader);
private:
	static string FileReader;//读者文件名
};


template<typename R>
BorrowBook<R>::BorrowBook()
{
	
}
template<typename R>
BorrowBook<R>::~BorrowBook()
{
}

template<typename R>
void BorrowBook<R>::getfilename(string filereader)
{
	FileReader = filereader;
}
//借书模块
template<typename R>
void BorrowBook<R>::borrow()
{
	//1、输入用户信息
	//2、输入要借的图书信息，并从文件中读出查找显示
	//3、选择要借的图书
	//4、将已经借了的图书信息更新到用户文件
	//5、更新图书文件
	R reader;
	Read_Write<R> userR_W;
	Read_Write<R>user;
	reader.getReaderCode(UserType::staticCode);//将用户ID传入

	ifstream file(FileReader);
	bool key3 = false;//用于验证

	//Reader文件存在判断是否此用户是否已经存在，如果存在，将信息提取出来并在Reader.txt中删除此用户信息，以便更新
	if (file)
	{
		user.ToRead(FileReader);
		for (unsigned i = 0; i < user.book.size(); i++)
		{
			if (user.book[i].putCode() == reader.putCode())//已经有借书记录的用户
			{
				userR_W.book.push_back(user.book[i]);//将此用户信息提取出来
				if ((user.book.begin() + i) != user.book.end())//再将此用户信息弹出，以便之后更新不会重复
				{
					user.book.erase(user.book.begin() + i);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
				}
				else
				{
					user.book.pop_back();//如果要删除的是最后一个元组的话
				}
				key3 = true;//老用户
				ofstream file1(FileReader, ios::trunc | ios::out);//将文件清空以便重新写入
				file1.close();
				user.ToWrite(FileReader);//再写入文件
			}
		}
	}
	if (key3 == false)
	{
		reader.getName();//新用户，输入姓名
	}
	Read_Write<Book> read;//read是book类型			
	int a = 0;
	Book *p = new Book[read.book.size()];//用于接收借书后要修改的图书信息
	Book *t = p;//t将用于对p 的重置
	string key2;//用于判断是否查找出需要借的图书，并对借书后的文件进行修改
	//找出需要借的图书
	while (true)
	{
		read.ToRead("book.txt");//每次循环重新读取book信息
		system("cls");
		p = t;//新一轮借书是重置P，
		cout << "········请输入你要借的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.book.size(); i++)//打印从txt中读取的结果
		{
			if ((read.book[i].m_strBookName.find(key) != string::npos) || (read.book[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read.book[i].displayBook();
				cout << endl;
				p = &(read.book[i]);
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
		for (unsigned i = 0; i < read.book.size(); i++)//嵌套太多，待优化
		{
			if (&(p[t - a - 1]) == &(read.book[i]))//先找到相同地址
			{
				if (read.book[i].m_iBookCount < 0 || read.book[i].m_iBookCount == 0)//再判断书数量为0，不可借
				{
					cout << "此书不可借" << endl;
					break;
				}
				else
				{
					read.book[i].m_iBookCount--;//还要找到地址，将文件进行修改
					reader.AddCount();
					reader.readerbook.push_back(read.book[i]);//将借书信息写入用户信息
					//将用户信息写入文件
					reader.getCount();
					if (key3)//此用户之前已经借过书
					{
						//userR_W.book.之前已经user.book[i]被实例化了,且userR_W.book只有一个元组
						userR_W.book[0].readerbook.insert(userR_W.book[0].readerbook.end(), reader.readerbook.begin(), reader.readerbook.end());
					}
					else//此用户之前未借过书
					{
						userR_W.book.push_back(reader);
					}
					userR_W.ToWrite(FileReader);//追加到Reader.txt 文件中
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

	/*delete[] p;
	p = NULL;*/
}

//还书
template<typename R>
void BorrowBook<R>::returnBook()
{
	//1、读取读者信息（不显示）
	//2、匹配用户名或ID
	//3、显示借书信息
	//4、选择要还图书
	//5、修改读者信息
	//6、修改文件信息
	Read_Write<R> returnR_W;
	returnR_W.ToRead(FileReader);//1、读取读者信息（不显示）
	while (true)
	{
		R reader;
		string key1, name;
		key1 = reader.getReaderCode(UserType::staticCode);//将用户ID传入		
		string key4;//判断是否继续还书vector<int>key7;//记录用户在vector流中的位置
		int key5;
		bool key2 = false;//判断用户是否存在
		for (unsigned i = 0; i < returnR_W.book.size(); i++)
		{
			if (returnR_W.book[i].putCode() == key1)//找到用户
			{
				key2 = true;
				reader = returnR_W.book[i];
				key5 = i;//记录用户在vector流中的位置
				returnR_W.book[i].display();//输出用户信息
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
			for (unsigned i = 0; i < bookR_W.book.size(); i++)
			{
				if (reader.readerbook[key3].m_strBookName == bookR_W.book[i].m_strBookName && reader.readerbook[key3].m_iBookCode == bookR_W.book[i].m_iBookCode)//在book.txt 中找到用户还的那本书
				{
					bookR_W.book[i].m_iBookCount++;
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
			returnR_W.book.insert(returnR_W.book.begin() + key5, reader);//在流的指定位置插入数据
			//将修改的信息写入ReaderInfo.txt
			ofstream file2(FileReader, ios::trunc | ios::out);//将文件清空以便重新写入
			file2.close();
			returnR_W.ToWrite(FileReader);//写入文件				

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

#endif