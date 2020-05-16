#include<iostream>
#include<string>
using namespace std;

class String
{
public:
	String(){ p = NULL; }
	String(char  *str);
	friend bool operator > (String &str1, String &str2);
	void display();
private:
	char *p;
};

String::String(char *str)
{
	p = str;
}

void String::display()
{
	cout << p;
}

bool operator>(String &str1, String &str2)
{
	if (strcmp(str1.p, str2.p) > 0)
		return true;
	else return false;
}

int main()
{
	String str1("hello"), str2("book");
	cout << (str1 > str2) << endl;
	getchar();
}