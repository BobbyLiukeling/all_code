#include<iostream>
#include<string>
#include<fstream>
#include"library.h"


using namespace std;

int main()
{
	library LIB;

	if (LIB.usertype()==true)//使用账号识别方法，若返回true则为管理员界面；否则返回false则为用户登录界面
	{		
			while (true)
			{

				switch (LIB.managelogin())//获取管理员的功能选择，返回为数字
				{
				case 1://查询图书
				{
					LIB.BookInventory();
					break;
				}
				case 2://更新图书信息
				{
					LIB.changeBook();
					break;
				}
				case 3://删除图书信息
				{
					LIB.DropBook();
					break;
				}
				case 4://添加图书信息
				{
					LIB.AddBook();//添加图书
					break;
				}
				case 5://查看用户信息
				{
					LIB.checktype();
				}
				default:
					break;
				}
				string key;
				cout << "是否继续管理员操作，是请按1，否请按任意键退出" << endl;
				cin >> key;
				if (key == "1")
				{
					continue;
				}
				else
				{
					break;
				}
			}
		
	}

	else //读者菜单
	{
		int chiose=LIB.ReaderType();
		
		while (true)
		{
			switch (LIB.Readerchiose())
			{

			case 1://查询图书
			{
				LIB.BookInventory();
				break;
			}
			case 2://借书
			{
				LIB.borrowtype(chiose);
				break;
			}
			case 3://还书
			{
				LIB.returntype(chiose);
				break;
			}
			default:
				break;
			}
			string key;
			cout << "是否继续操作，是请按1，否请按任意键退出" << endl;
			cin >> key;
			if (key == "1")
			{
				continue;
			}
			else
			{
				break;
			}
		}
	}
	

	system("pause");

	return 0;
}