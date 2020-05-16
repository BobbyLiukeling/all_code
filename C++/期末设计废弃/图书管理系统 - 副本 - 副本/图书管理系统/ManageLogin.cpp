#include<iostream>
#include"ManageLogin.h"

using namespace std;

ManageLogin::ManageLogin()
{
}

ManageLogin::~ManageLogin()
{
}

bool ManageLogin::getAdmin(string code)
{
	cout << "hello Manage： " << code << endl;

	string admin;
	while (1)
	{
		cout << "请输入密码： ";
		cin >> admin;
		/*cout << "m_strCode: " << m_strAdmin << "  " << m_strAdmin.size() << endl;
		cout << "admin: " << admin << "  " << admin.size() << endl;*/
		if (admin == code)
		{
			cout << "欢迎加入管理系统" << endl;
			return true;
			break;
		}
		else
		{
			cout << "您输入的密码不正确，请重新输入"<<endl;
			cout << "是否重新输入，是请按:Y，否请按任意键退出" << endl;
			string key;
			cin >> key;
			if (key=="y"||key=="Y")
			continue;
			else
			{   cout << "您选择了退出" << endl;
			    return false;
				break;
			}
		}
	}
}

int ManageLogin::ManageChiose()
{
	system("cls");//清屏
	cout << "···请选择您想要继续的操作，并输入相应序号···" <<endl;
	cout << "··········1、查看图书··········" << endl;
	cout << "··········2、更新图书··········" << endl;
	cout << "··········3、删除图书··········" << endl;
	cout << "··········4、增加图书··········" << endl;
	cout << "··········5、读者信息··········" << endl;
	int chiose;
	while(true)
	{
    cin >> chiose;
	if (chiose == 1 || chiose == 2 || chiose == 3 || chiose == 4||chiose==5)
	{
		return chiose;
		break;
	}
	else
	{
		cout << "您输入的选择不正确，请重新输入"<<endl;
		cout << "是否继续选择，是请按：1，否请按：0" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			continue;
		}
		else
		{
			cout << "您选择了退出" << endl;
			return 0;
			break;
		}
	}
	}	
}

int ManageLogin::ReaderChiose()//读者选项
{
	system("cls");//清屏
	cout << "用户：" << UserType::staticCode<<endl;
	cout << "···请选择您想要继续的操作，并输入相应序号···" << endl;
	cout << "··········1、查找图书··········" << endl;
	cout << "··········2、借书··········" << endl;
	cout << "··········3、还书··········" << endl;
	int chiose;
	while (true)
	{
		cin >> chiose;
		if (chiose == 1 || chiose == 2 || chiose == 3)
		{
			return chiose;
			break;
		}
		else
		{
			cout << "您输入的选择不正确，请重新输入" << endl;
			cout << "是否继续选择，是请按：1，否请按：0" << endl;
			int a;
			cin >> a;
			if (a == 1)
			{
				continue;
			}
			else
			{
				cout << "您选择了退出" << endl;
				return 0;
				break;
			}
		}
	}
}