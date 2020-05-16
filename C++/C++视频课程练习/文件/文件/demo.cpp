#include <fstream>
#include <iostream>
#include<string>
#include<vector>

using namespace std;

class UserType
{
public:	
	UserType(string code)
	{
		m_strCode = code;
	}
	void diaplay()
	{
		cout << m_strCode << endl;
	}
private:
	string m_strCode;
};

int main()
{
	vector<UserType> user;
	UserType user1("lkl"),user2("bobby"),user3("lalalal"),user4("dpdpdpd");
	user.push_back(user1);
	user.push_back(user2);
	user.push_back(user3);
	user.push_back(user4);
	/*user[2].diaplay();
	user[4].diaplay();
	cout << user.size() << endl;
	user.erase(user.begin() + 3);
	user[3].diaplay();
	cout << user.size() << endl;*/
	cout << user.size() << endl;
	for (unsigned i = 0; i < user.size(); i++)
	{
		user[i].diaplay();
	}
	user.pop_back();
	cout << user.size() << endl;
	for (unsigned i = 0; i < user.size(); i++)
	{
		user[i].diaplay();
	}
	system("pause");
	return 0;

}