#ifndef _MANAGELOGIN_H
#define _MANAGELOGIN_H

#include<string>
#include"UserType.h"
using namespace std;
//验证管理员密码
class ManageLogin
{
public:
	ManageLogin();
	~ManageLogin();
	bool getAdmin(string code);//输入管理员密码并判断密码是否正确
	int ManageChiose();
	int ReaderChiose();
private:
	string m_strAdmin;
};

#endif