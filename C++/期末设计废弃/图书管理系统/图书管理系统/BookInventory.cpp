#include"BookInventory.h"
//空的构造器
BookInventory::BookInventory()
{
	
}

void BookInventory::printBook()
{
	//1、输入查询内容
	//2、按条件读取并打印
	Read_Write <Book> read;//将文件内容读到book数组中去
	read.ToRead("book.txt");//读取txt中的内容
	cout << "········查询所有图书请按1········" << endl;
	cout << "·········精确查询请按2·········" << endl;
	cout << "·········按任意键退出·········" << endl;
	string key;
	cin >> key;
	while (true)
	{
		if (key == "1")
		{ 
			for (unsigned i = 0; i <read.book.size(); i++)//打印从txt中读取的结果
			{
			read.book[i].displayBook();
			}
			break;
		}
		if (key == "2")//自定义模糊查询
		{
			cout << "······请输入需要查询的图书名称或编号······" << endl;
			string key1;
			cin >> key1;
			int a=0;
			for (unsigned i = 0; i < read.book.size(); i++)//打印从txt中读取的结果
			{
				if ((read.book[i].m_strBookName.find(key1) != string::npos) || (read.book[i].m_iBookCode.find(key1) != string::npos))
				{
					cout << "与 “" << key1 << "” 相关的图书信息:";
					read.book[i].displayBook();
					cout << endl;
					a++;//记录查询出的本数
				}
			}
			if (a == 0)
			{
				cout << "没有您要找的图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;
				string key2;
				cin >> key2;
				if (key2 == "1")
					continue;
				else
				{
					cout << "您退出了查询" << endl;
					break;
				}
			}
			break;
		}
	}
}

BookInventory::~BookInventory()
{

}