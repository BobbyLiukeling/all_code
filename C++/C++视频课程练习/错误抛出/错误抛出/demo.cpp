#include<iostream>
#include"IndexException.h"

using namespace std;

void test()
{
	throw 10;
}

int main()
{
	try
	{
		test();
	}
	catch (int&e)
	{
		cout << "exception:"<<e << endl;
	}
	/*catch (CFileException *e)
	{

	}
	catch (CException *e)
	{

	}*/

	
	getchar();
	return 0;
}
