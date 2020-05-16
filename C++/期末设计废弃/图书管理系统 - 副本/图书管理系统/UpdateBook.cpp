#include"UpdateBook.h"

UpdateBook::UpdateBook()
{
}

void UpdateBook::changeBook()
{
	//1、读取图书文件
	//2、模糊查询待修改图书
	//3、选择待修改的图书及内容，并输入修改内容
	//4、更新文件信息
	Read_Write<Book> read;
	read.ToRead("book.txt");
	int a = 0;
	Book *p = new Book[100];//用于接收需要修改的图书
	string key2;//用于判断是否查找出需要修改的图书，及判断是否进行内容修改
	while (true)//找出需要修改的图书
	{
		system("cls");
		cout << "········请输入你更新的图书名称或者图书编号········" << endl;
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
			cout << "没有您要修改图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;

			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了修改" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出修改
	{

		int t;
		if (a == 1)
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要更新的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		cout << "请选择你要修改的内容" << endl;
		cout << "1、书名    " << "2、编号    " << "3、图书数目" << endl;
		int chiose;
		cin >> chiose;
		switch (chiose)
		{
		case 1:
		{
			cout << "请输入新的书名" << endl;
			string name;
			cin >> name;
			p[t - a].m_strBookName = name;
			break;
		}
		case 2:
		{
			cout << "请输入新的编号" << endl;
			string code;
			cin >> code;
			p[t - a].m_iBookCode = code;
			break;
		}
		case 3:
		{
			cout << "请输入新的图书数目" << endl;
			int count;
			cin >> count;
			p[t - a].m_iBookCount = count;
			break;
		}
		default:
			cout << "您的选择不正确" << endl;
			break;
		}
		//还要找到地址，将文件进行修改
		for (unsigned i = 0; i < read.book.size(); i++)
		{
			if (&(p[t - a]) == &(read.book[i]))//地址相同时	
			{
				cout << "找到地址相同的book" << endl;
				read.book[i] = *p;
			}
		}
		cout << "继续修改请按1，否则按任意键退出" << endl;
		string key3;
		cin >> key3;
		if (key3 == "1")
		{ 
			continue;
		}
		else
		{
			cout << "修改结束" << endl;
			break;
		}
	}//while结束

	//将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	read.ToWrite("book.txt");
	
	delete[] p;
	p = NULL;//内存释放出现问题，其他的正常
}

void UpdateBook::DropBook()
{
	//1、读出图书信息并江上编号打印
	//2、选择要删除的图书编号
	//3、删除图书,注意尾指针的变化
	//4、更新文件
	Read_Write<Book> drop;
	drop.ToRead("book.txt");
	top = 0;
	for (unsigned i = 0; i < drop.book.size(); i++)//打印从txt中读取的结果
	{
		top++;
		cout << "第 " << top << " 本图书" << endl;
		drop.book[i].displayBook();
	}
	int key1;	
	while (true)
	{
		cout << "请选择你要删除的图书序号" << endl;
		cin >> key1;
		if (key1 >= 0 && key1 <= top)
		{
			if ((drop.book.begin() + (key1 - 1)) != drop.book.end())
			{
				drop.book.erase(drop.book.begin() + (key1 - 1));//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				drop.book.pop_back();//如果要删除的是最后一个元组的话
			}

			cout << "是否要继续删除" << endl << "是请按1，否则按任意键退出" << endl;
			string key2;
			if (key2 == "1")//判断是否继续删除
			{
				continue;
			}
			else
			{
				cout << "删除完毕，已退出" << endl;
				break;
			}
		}
		else
		{
			cout << "请正确输入" << endl << "重新输入请按1，否则按任意键退出";
			string key3;
			if (key3 == "1")
			{ 
				continue;
			}
			else
			{
				cout << "您退出了删除图书操作" << endl;
				break;
			}
		}
	}
	//将文件清空，再重新写入删除后的内容
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	drop.ToWrite("book.txt");
}

UpdateBook::~UpdateBook()
{
}