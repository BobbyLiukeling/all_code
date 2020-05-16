#include<iostream>
#include"UserType.h"

using namespace std;

//UserType::UserType()
//{
//	m_strCode = "01";//默认登录为管理员
//}

UserType::~UserType()
{

}
string UserType::staticCode = "0001";

bool UserType::selectCode()//账号输入判断
{
	string code;
	while (true)
	{
		cout << "请输入两位数管理员账号，或者用户四位数账号：" << endl;
		cin >> code;
		m_strCode = code;
		if (m_strCode.size() == 2)//管理员两位数账号
		{			
			return true;
			break;
		}

		if (m_strCode.size() == 4)//用户四位数账号
		{			
			staticCode = m_strCode;
			//cout << "判断账号输入staticCode:" << staticCode << endl;
			return false;
			break;
		}

		else//账号输入不正确
		{
			cout << "请正确输入账号" << endl;
			continue;
		}
	}
}

void UserType::display()
{
	cout << m_strCode << endl;
}


string UserType::getCode()
{
	return m_strCode;
}
