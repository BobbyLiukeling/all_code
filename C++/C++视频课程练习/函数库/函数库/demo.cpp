#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<map>

using namespace std;

int main()
{
	//vector<int>vec;
	//vec.push_back(7);
	//vec.push_back(4);
	//vec.push_back(9);
	//vec.pop_back();
	//cout << vec.size() << endl;
	//for (int i = 0; i < vec.size(); i++)
	//{
	//	cout << vec[i] << endl;
	//}

	//vector<int>::iterator it = vec.begin();
	////迭代器，it是指针指向vec 的首地址
	//cout << *it << endl;
	//for (; it != vec.end(); it++)
	//{
	//	cout << *it << endl; 
	//}

	//cout<<"定一个数据"<<vec.front()<<endl;//打印出第一个数据
	//cout << "最后一个数据" << vec.back() << endl;//打印出最后一个数据

    
	/*list<int>list1; 
	list1.push_back(2);
	list1.push_back(5);
	list1.push_back(7);

	list<int>::iterator t = list1.begin();
	for (; t != list1.end(); t++)
	{
		cout << *t << endl;
	}*/



	/*map<int, string>m;
	pair<int, string>p1(4, "hello");
	pair<int, string>p2(3, "C++");
	m.insert(p1);
	m.insert(p2);

	cout << m[4] << endl;
	cout << m[3] << endl;

	map <int,string>::iterator ma = m.begin();
	for (; ma != m.end(); ma++)
	{
		cout <<"映射键内容输出："<< ma->first << endl;
		cout << "映射值内容输出：" << ma->second << endl<<endl;
	}*/

	map<string, string>m1;
	pair<string, string>p3("H", "Hello");
	pair<string, string>p4("B", "Beijing");
	pair<string, string>p5("S", "Shanghai");
	m1.insert(p3);
	m1.insert(p4);
	m1.insert(p5);
	cout << m1["B"] << endl;

	map <string, string>::iterator ma1 = m1.begin();
	for (; ma1 != m1.end(); ma1++)
	{
		cout << "映射键内容输出：" << ma1->first << endl;
		cout << "映射值内容输出：" << ma1->second << endl << endl;
	}
	getchar();
	return 0;
}






