#include"AddBook.h"

//int AddBook::m_iSum = 0;//初始化sum

AddBook::AddBook()
{
	m_iSum = 0;
}

void AddBook::getBook()
{
	//1、输入图书信息
	//2、将图书信息写入文件
	string name;
	string code;
	int count;
	string key;
	Read_Write<Book> R_W;
	while (1)
	{
		cout << "请输入图书名称" << endl;
		cin >> name;
		cout << "请输入图书编号" << endl;
		cin >> code;
		cout << "请输入此类图书的数目" << endl;
		cin >> count;
		Book b(name, code, count);
		m_iSum++;
		R_W.book.push_back(b);
		cout << "是否继续录入图书，是：请按y(Y)，否：按任意键退出" << endl;
		cin >> key;
		if (key != "y" && key != "Y")//判断是否继续输入
			break;
	}
	R_W.ToWrite("book.txt");//读入文件
	
}

AddBook::~AddBook()
{
}