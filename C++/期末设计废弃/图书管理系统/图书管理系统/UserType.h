#ifndef _USERTYPE_H
#define _USERTYPE_H
//判断用户类型
#include<string>
using namespace std;

class UserType
{
public:
	//UserType() :m_strCode("01"){}
	virtual ~UserType();
	bool selectCode();
	void display();
	string getCode();
	string m_strCode;
	static string staticCode;//便于记录读者ID；
};

#endif

