#include<iostream>
#include<string>
#include"ManageLogin.h"//管理员登录
#include"AddBook.h"//添加图书
#include"BookInventory.h"
#include"UpdateBook.h"
#include"Reader.h"
#include"BorrowBook.h"
#include"Read_Write.h"
#include"ReaderType.h"
#include"CheckReader.h"

using namespace std;

int main()
{
	UserType usertype;
	ManageLogin managelogin;

	if (usertype.selectCode())//使用账号识别方法，若返回true则为管理员界面；否则返回false则为用户登录界面
	{
		if (managelogin.getAdmin(usertype.getCode()))//获取管理员输入的账号，并进行密码校验
		{
			while (true)
			{

				switch (managelogin.ManageChiose())//获取管理员的功能选择，返回为数字
				{
				case 1://查询图书
				{
					BookInventory B;
					B.printBook();//管理员进行查询
					break;
				}
				case 2://更新图书信息
				{
					UpdateBook updatebook;
					updatebook.changeBook();
					break;
				}
				case 3://删除图书信息
				{
					UpdateBook updatebook;
					updatebook.DropBook();
					break;
				}
				case 4://添加图书信息
				{
					AddBook addbook;
					addbook.getBook();//添加图书
					break;
				}
				case 5://查看用户信息
				{
					CheckReader check;
					check.checktype();
					break;
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
	}

	else //读者菜单
	{
		ReaderType readertype;
		int a = readertype.Readertype();
		while (true)
		{
			switch (managelogin.ReaderChiose())
			{

			case 1://查询图书
			{
				BookInventory B;
				B.printBook();//查询
				break;
			}
			case 2://借书
			{
				BorrowBook Borrow;
				Borrow.borrow(a);
				break;
			}
			case 3://还书
			{
				BorrowBook Borrow;
				Borrow.returnBook(a);
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