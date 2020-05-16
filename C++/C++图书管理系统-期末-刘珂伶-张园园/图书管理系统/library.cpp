#include"library.h"
using namespace std;

library::library()
{
}

library::~library()
{
}

int library::m_strRCode = 10;
bool library::usertype()
{
	int code;
	while (true)
	{
		cout << "请输入两位数管理员账号，或者用户四位数账号：" << endl;
		cin >> code;
		m_strRCode = code;
		if (m_strRCode > 9 && m_strRCode < 100)//管理员两位数账号
		{
			return true;
			break;
		}

		if (m_strRCode>99 && m_strRCode < 10000)//用户四位数账号
		{
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

int library::managelogin()
{
	system("cls");//清屏
	cout << "···请选择您想要继续的操作，并输入相应序号···" << endl;
	cout << "··········1、查看图书··········" << endl;
	cout << "··········2、更新图书··········" << endl;
	cout << "··········3、删除图书··········" << endl;
	cout << "··········4、增加图书··········" << endl;
	cout << "··········5、读者信息··········" << endl;
	int chiose;
	while (true)
	{
		cin >> chiose;
		if (chiose == 1 || chiose == 2 || chiose == 3 || chiose == 4 || chiose == 5)
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

void library::BookInventory()
{

	//1、输入查询内容
	//2、按条件读取并打印
	vector<Book> read(Read<Book>("book.txt"));
	cout << "········查询所有图书请按1········" << endl;
	cout << "·········精确查询请按2·········" << endl;
	cout << "·········按任意键退出·········" << endl;
	string key;
	cin >> key;
	while (true)
	{
		if (key == "1")
		{
			for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
			{
				read[i].displayBook();
			}
			break;
		}
		if (key == "2")//自定义模糊查询
		{
			cout << "······请输入需要查询的图书名称或编号······" << endl;
			string key1;
			cin >> key1;
			int a = 0;
			for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
			{
				if ((read[i].m_strBookName.find(key1) != string::npos) || (read[i].m_iBookCode.find(key1) != string::npos))
				{
					cout << "与 “" << key1 << "” 相关的图书信息:";
					read[i].displayBook();
					cout << endl;
					a++;//记录查询出的本数
				}
			}
			if (a == 0)
			{
				cout << "没有您要找的图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;
				string key2;
				cin >> key2;
				if (key2 == "1")
					continue;
				else
				{
					cout << "您退出了查询" << endl;
					break;
				}
			}
			break;
		}
	}

}

void library::changeBook()
{
	//1、读取图书文件
	//2、模糊查询待修改图书
	//3、选择待修改的图书及内容，并输入修改内容
	//4、更新文件信息
	vector<Book> read(Read<Book>("book.txt"));
	int a = 0;
	Book *p = new Book[100];//用于接收需要修改的图书
	string key2;//用于判断是否查找出需要修改的图书，及判断是否进行内容修改
	while (true)//找出需要修改的图书
	{
		system("cls");
		cout << "········请输入你更新的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
		{
			if ((read[i].m_strBookName.find(key) != string::npos) || (read[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read[i].displayBook();
				cout << endl;
				p = &(read[i]);
				p++;
			}
		}
		if (a == 0)//未规范输入判断
		{
			cout << "没有您要修改图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;

			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了修改" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出修改
	{

		int t;
		if (a == 1)
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要更新的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		cout << "请选择你要修改的内容" << endl;
		cout << "1、书名    " << "2、编号    " << "3、图书数目" << endl;
		int chiose;
		cin >> chiose;
		switch (chiose)
		{
		case 1:
		{
			cout << "请输入新的书名" << endl;
			string name;
			cin >> name;
			p[t - a].m_strBookName = name;
			break;
		}
		case 2:
		{
			cout << "请输入新的编号" << endl;
			string code;
			cin >> code;
			p[t - a].m_iBookCode = code;
			break;
		}
		case 3:
		{
			cout << "请输入新的图书数目" << endl;
			int count;
			cin >> count;
			p[t - a].m_iBookCount = count;
			break;
		}
		default:
			cout << "您的选择不正确" << endl;
			break;
		}
		//还要找到地址，将文件进行修改
		for (unsigned i = 0; i < read.size(); i++)
		{
			if (&(p[t - a]) == &(read[i]))//地址相同时	
			{
				swap(read[i], (p[t - a]));
				cout << "修改成功" << endl;

			}
		}

		cout << "继续修改请按1，否则按任意键退出" << endl;
		string key3;
		cin >> key3;
		if (key3 == "1")
		{
			continue;
		}
		else
		{
			cout << "修改结束" << endl;
			break;
		}
	}//while结束

	//将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);
	//delete[] p;
	//p = NULL;//内存释放出现问题，其他的正常
}

void library::DropBook()
{
	//1、读出图书信息并江上编号打印
	//2、选择要删除的图书编号
	//3、删除图书,注意尾指针的变化
	//4、更新文件
	vector<Book> read(Read<Book>("book.txt"));
	int top = 0;
	for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
	{
		top++;
		cout << "第 " << top << " 本图书" << endl;
		read[i].displayBook();
	}
	int key1;
	while (true)
	{
		cout << "请选择你要删除的图书序号" << endl;
		cin >> key1;
		if (key1 >= 0 && key1 <= top)
		{
			if ((read.begin() + (key1 - 1)) != read.end())
			{
				read.erase(read.begin() + (key1 - 1));//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				read.pop_back();//如果要删除的是最后一个元组的话
			}

			cout << "是否要继续删除" << endl << "是请按1，否则按任意键退出" << endl;
			string key2;
			if (key2 == "1")//判断是否继续删除
			{
				continue;
			}
			else
			{
				cout << "删除完毕，已退出" << endl;
				break;
			}
		}
		else
		{
			cout << "请正确输入" << endl << "重新输入请按1，否则按任意键退出";
			string key3;
			if (key3 == "1")
			{
				continue;
			}
			else
			{
				cout << "您退出了删除图书操作" << endl;
				break;
			}
		}
	}
	//将文件清空，再重新写入删除后的内容
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);
}

void library::AddBook()
{

	//1、输入图书信息
	//2、将图书信息写入文件
	string name;
	string code;
	int count;
	string key;
	vector<Book> read(Read<Book>("book.txt"));
	while (1)
	{
		cout << "请输入图书名称" << endl;
		cin >> name;
		cout << "请输入图书编号" << endl;
		cin >> code;
		cout << "请输入此类图书的数目" << endl;
		cin >> count;
		Book b(name, code, count);
		read.push_back(b);
		cout << "是否继续录入图书，是：请按y(Y)，否：按任意键退出" << endl;
		cin >> key;
		if (key != "y" && key != "Y")//判断是否继续输入
			break;
	}
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);//读入文件
}

int library::ReaderType()
{
	cout << "请选择读者类型：" << endl;
	cout << "1、教职工读者用户" << endl;
	cout << "2、学生读者用户" << endl;
	cout << "3、校外读者用户" << endl;
	int key1;
	while (1)//选择读者用户类型
	{
		cin >> key1;
		if (key1 == 1 || key1 == 2 || key1 == 3)
		{
			break;
		}
		else
		{
			cout << "输入不正确" << endl;
			cout << "重新输入请按1，否则按任意键退出" << endl;
			string key2;
			cin >> key2;
			if (key2 == "1")
			{
				cout << "请重新输入：" << endl;
				continue;
			}
			else
			{
				break;
				key1 = 0;
			}
		}

	}

	return key1;
}

int library::Readerchiose()
{
	system("cls");//清屏
	cout << "用户：" << m_strRCode << endl;
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

void library::checktype()
{
	cout << "请选择查看的读者类型：" << endl;
	cout << "1、教职工读者用户" << endl;
	cout << "2、学生读者用户" << endl;
	cout << "3、校外读者用户" << endl;
	int key1;
	cin >> key1;
	switch (key1)
	{
	case 1:
	{     
		vector<Teacher_Reader>read(Read<Teacher_Reader>("Teacher_Reader.txt"));
	for (unsigned i = 0; i < read.size(); i++)
	{
		read[i].display();
	}
	break;
	}
	case 2:
	{
		vector<Student_Reader> read(Read<Student_Reader>("Student_Reader.txt"));

		for (unsigned i = 0; i < read.size(); i++)
		{
			read[i].display();
		}
		break;
	}
	case 3:
	{
		vector<Outside_campus_Reader> read(Read<Outside_campus_Reader>("Outside_campus_Reader.txt"));
		for (unsigned i = 0; i < read.size(); i++)
		{
			read[i].display();
		}
		break;
	}
	default:
		break;
	}
}

void library::borrow(Teacher_Reader reader, string filename)
{
	//1、输入用户信息
	//2、输入要借的图书信息，并从文件中读出查找显示
	//3、选择要借的图书
	//4、将已经借了的图书信息更新到用户文件
	//5、更新图书文件
	vector<Teacher_Reader> Teacher;
	ifstream file(filename);
	bool key3 = false;//用于验证

	//Reader文件存在判断是否此用户是否已经存在，如果存在，将信息提取出来并在Reader.txt中删除此用户信息，以便更新
	if (file)
	{
		vector<Teacher_Reader> teacher_reader(Read<Teacher_Reader>(filename));
		for (unsigned i = 0; i < teacher_reader.size(); i++)
		{
			if (teacher_reader[i].putCode() == reader.putCode())//已经有借书记录的用户
			{
				Teacher.push_back(teacher_reader[i]);//将此用户信息提取出来
				if ((teacher_reader.begin() + i) != teacher_reader.end())//再将此用户信息弹出，以便之后更新不会重复
				{
					teacher_reader.erase(teacher_reader.begin() + i);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
				}
				else
				{
					teacher_reader.pop_back();//如果要删除的是最后一个元组的话
				}
				key3 = true;//老用户
				ofstream file1(filename, ios::trunc | ios::out);//将文件清空以便重新写入
				file1.close();
				Write(filename, teacher_reader);//再写入文件
			}
		}
	}
	if (key3 == false)
	{
		reader.getName();//新用户，输入姓名
	}

	vector<Book> read(Read<Book>("book.txt"));
	int a = 0;
	Book *p = new Book[read.size()];//用于接收借书后要修改的图书信息
	string key2;//用于判断是否查找出需要借的图书，并对借书后的文件进行修改
	while (true)//找出需要借的图书
	{
		system("cls");
		cout << "········请输入你要借的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
		{
			if ((read[i].m_strBookName.find(key) != string::npos) || (read[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read[i].displayBook();
				cout << endl;
				p = &(read[i]);
				p++;
			}
		}
		if (a == 0)//未规范输入判断
		{
			cout << "没有您要借图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;
			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了借书" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出借书
	{
		int t;
		if (a == 1)//只查询出一本与此相关的书
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要借的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		if (key3 == true)//老用户，判断是否已借过此书
		{
			for (unsigned i = 0; i < Teacher[0].readerbook.size(); i++)
			{
				for (unsigned i = 0; i < read.size(); i++)
				{
					if (&(p[t - a - 1]) == &(read[i]) && Teacher[0].readerbook[i].m_iBookCode == read[i].m_iBookCode)//用此户已借过这本书了，不再借
					{
						cout << "此书您还未归还,不能再借此书" << endl;
						break;
					}
				}
			}
		}

		for (unsigned i = 0; i < read.size(); i++)//嵌套太多，待优化
		{
			if (&(p[t - a - 1]) == &(read[i]))//先找到相同地址
			{
				if (read[i].m_iBookCount < 0 || read[i].m_iBookCount == 0)//再判断书数量为0，不可借
				{
					cout << "此书不可借" << endl;
					break;
				}
				else
				{
					read[i].m_iBookCount--;//还要找到地址，将文件进行修改
					reader.AddCount();
					reader.readerbook.push_back(read[i]);//将借书信息写入用户信息
					//将用户信息写入文件
					reader.getCount();
					if (key3)//此用户之前已经借过书
					{
						//Teacher之前已经read[i]被实例化了,且Teacher只有一个元组
						Teacher[0].readerbook.insert(Teacher[0].readerbook.end(), reader.readerbook.begin(), reader.readerbook.end());
					}
					else//此用户之前未借过书
					{
						Teacher.push_back(reader);
					}
					Write(filename, Teacher);//追加到Reader.txt 文件中
					break;
				}
			}
		}
		cout << "借书结束" << endl;
		break;

	}//外层while结束

	//借书完成将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);
}

void library::borrow(Student_Reader reader, string filename)
{
	//1、输入用户信息
	//2、输入要借的图书信息，并从文件中读出查找显示
	//3、选择要借的图书
	//4、将已经借了的图书信息更新到用户文件
	//5、更新图书文件
	vector<Student_Reader> Student;
	ifstream file(filename);
	bool key3 = false;//用于验证

	//Reader文件存在判断是否此用户是否已经存在，如果存在，将信息提取出来并在Reader.txt中删除此用户信息，以便更新
	if (file)
	{
		vector<Student_Reader> student_reader(Read<Student_Reader>(filename));
		for (unsigned i = 0; i < student_reader.size(); i++)
		{
			if (student_reader[i].putCode() == reader.putCode())//已经有借书记录的用户
			{
				Student.push_back(student_reader[i]);//将此用户信息提取出来
				if ((student_reader.begin() + i) != student_reader.end())//再将此用户信息弹出，以便之后更新不会重复
				{
					student_reader.erase(student_reader.begin() + i);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
				}
				else
				{
					student_reader.pop_back();//如果要删除的是最后一个元组的话
				}
				key3 = true;//老用户
				ofstream file1(filename, ios::trunc | ios::out);//将文件清空以便重新写入
				file1.close();
				Write(filename, student_reader);//再写入文件
			}
		}
	}
	if (key3 == false)
	{
		reader.getName();//新用户，输入姓名
	}

	vector<Book> read(Read<Book>("book.txt"));
	int a = 0;
	Book *p = new Book[read.size()];//用于接收借书后要修改的图书信息
	string key2;//用于判断是否查找出需要借的图书，并对借书后的文件进行修改
	while (true)//找出需要借的图书
	{
		system("cls");
		cout << "········请输入你要借的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
		{
			if ((read[i].m_strBookName.find(key) != string::npos) || (read[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read[i].displayBook();
				cout << endl;
				p = &(read[i]);
				p++;
			}
		}
		if (a == 0)//未规范输入判断
		{
			cout << "没有您要借图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;
			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了借书" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出借书
	{
		int t;
		if (a == 1)//只查询出一本与此相关的书
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要借的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		for (unsigned i = 0; i < read.size(); i++)//嵌套太多，待优化
		{
			if (&(p[t - a - 1]) == &(read[i]))//先找到相同地址
			{
				if (read[i].m_iBookCount < 0 || read[i].m_iBookCount == 0)//再判断书数量为0，不可借
				{
					cout << "此书不可借" << endl;
					break;
				}
				else
				{
					read[i].m_iBookCount--;//还要找到地址，将文件进行修改
					reader.AddCount();
					reader.readerbook.push_back(read[i]);//将借书信息写入用户信息
					//将用户信息写入文件
					reader.getCount();
					if (key3)//此用户之前已经借过书
					{
						//Student之前已经read[i]被实例化了,且Student只有一个元组
						Student[0].readerbook.insert(Student[0].readerbook.end(), reader.readerbook.begin(), reader.readerbook.end());
					}
					else//此用户之前未借过书
					{
						Student.push_back(reader);
					}
					Write(filename, Student);//追加到Reader.txt 文件中
					break;
				}
			}
		}
		cout << "借书结束" << endl;
		break;

	}//外层while结束

	//借书完成将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);
}

void library::borrow(Outside_campus_Reader reader, string filename)
{
	//1、输入用户信息
	//2、输入要借的图书信息，并从文件中读出查找显示
	//3、选择要借的图书
	//4、将已经借了的图书信息更新到用户文件
	//5、更新图书文件
	vector<Outside_campus_Reader> Outside;
	ifstream file(filename);
	bool key3 = false;//用于验证

	//Reader文件存在判断是否此用户是否已经存在，如果存在，将信息提取出来并在Reader.txt中删除此用户信息，以便更新
	if (file)
	{
		vector<Outside_campus_Reader> outside_campus_reader(Read<Outside_campus_Reader>(filename));
		for (unsigned i = 0; i < outside_campus_reader.size(); i++)
		{
			if (outside_campus_reader[i].putCode() == reader.putCode())//已经有借书记录的用户
			{
				Outside.push_back(outside_campus_reader[i]);//将此用户信息提取出来
				if ((outside_campus_reader.begin() + i) != outside_campus_reader.end())//再将此用户信息弹出，以便之后更新不会重复
				{
					outside_campus_reader.erase(outside_campus_reader.begin() + i);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
				}
				else
				{
					outside_campus_reader.pop_back();//如果要删除的是最后一个元组的话
				}
				key3 = true;//老用户
				ofstream file1(filename, ios::trunc | ios::out);//将文件清空以便重新写入
				file1.close();
				Write(filename, outside_campus_reader);//再写入文件
			}
		}
	}
	if (key3 == false)
	{
		reader.getName();//新用户，输入姓名
	}

	vector<Book> read(Read<Book>("book.txt"));
	int a = 0;
	Book *p = new Book[read.size()];//用于接收借书后要修改的图书信息
	string key2;//用于判断是否查找出需要借的图书，并对借书后的文件进行修改
	while (true)//找出需要借的图书
	{
		system("cls");
		cout << "········请输入你要借的图书名称或者图书编号········" << endl;
		string key;
		cin >> key;
		for (unsigned i = 0; i < read.size(); i++)//打印从txt中读取的结果
		{
			if ((read[i].m_strBookName.find(key) != string::npos) || (read[i].m_iBookCode.find(key) != string::npos))
			{
				a++;//记录查询出的本数
				cout << "与 “" << key << "” 相关的第 " << a << " 本图书信息:" << endl;
				read[i].displayBook();
				cout << endl;
				p = &(read[i]);
				p++;
			}
		}
		if (a == 0)//未规范输入判断
		{
			cout << "没有您要借图书，请规范你的输入。重新输入请按1，退出请按任意键" << endl;
			cin >> key2;
			if (key2 == "1")
				continue;
			else
			{
				cout << "您退出了借书" << endl;
				break;
			}
		}
		else
			break;//查询到结果退出查询		
	}

	while (key2 != "1")//未退出借书
	{
		int t;
		if (a == 1)//只查询出一本与此相关的书
		{
			t = 1;
		}
		else
		{
			cout << "请输入您要借的图书的序号" << endl;
			cin >> t;
		}
		cout << "——————————————————————————————————————————————" << endl;
		for (unsigned i = 0; i < read.size(); i++)//嵌套太多，待优化
		{
			if (&(p[t - a - 1]) == &(read[i]))//先找到相同地址
			{
				if (read[i].m_iBookCount < 0 || read[i].m_iBookCount == 0)//再判断书数量为0，不可借
				{
					cout << "此书不可借" << endl;
					break;
				}
				else
				{
					read[i].m_iBookCount--;//还要找到地址，将文件进行修改
					reader.AddCount();
					reader.readerbook.push_back(read[i]);//将借书信息写入用户信息
					//将用户信息写入文件
					reader.getCount();
					if (key3)//此用户之前已经借过书
					{
						//Outside之前已经read[i]被实例化了,且Outside只有一个元组
						Outside[0].readerbook.insert(Outside[0].readerbook.end(), reader.readerbook.begin(), reader.readerbook.end());
					}
					else//此用户之前未借过书
					{
						Outside.push_back(reader);
					}
					Write(filename, Outside);//追加到Reader.txt 文件中
					break;
				}
			}
		}
		cout << "借书结束" << endl;
		break;

	}//外层while结束

	//借书完成将文件清空，再重新写入
	ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
	file1.close();
	Write("book.txt", read);
}

void library::Return(Teacher_Reader reader, string filename)
{
	//1、读取读者信息（不显示）
	//2、匹配用户名或ID
	//3、显示借书信息
	//4、选择要还图书
	//5、修改读者信息
	//6、修改文件信息

	vector<Teacher_Reader> teacher_reader(Read<Teacher_Reader>(filename));
	while (true)
	{
		string name;
		string key4;//判断是否继续还书vector<int>key7;//记录用户在vector流中的位置
		int key5;//记录用户在文件中的位置
		bool key2 = false;//判断用户是否存在
		for (unsigned i = 0; i < teacher_reader.size(); i++)
		{
			if (teacher_reader[i].putCode() == m_strRCode)//找到用户
			{
				key2 = true;
				reader = teacher_reader[i];
				//cout << "查询出的第 " << reader.size() << " 位用户" << endl;
				key5 = i;//记录用户在vector流中的位置
				teacher_reader[i].display();//输出用户信息
			}
		}

		//不存在此用户
		if (key2 == false)
		{
			cout << "此用户不存在，您还未借书" << endl;
			break;
		}
		if (reader.readerbook.size() < 1)
		{
			cout << "您还未借书" << endl;
			break;
		}

		//此用户存在,且有未还书
		else
		{
			cout << "请输入要归还的图书序号" << endl;
			int key3;
			cin >> key3;

			//将修改的信息写入Book.txt  和  ReaderInfo.txt
			vector<Book> bookR_W(Read<Book>("book.txt"));
			for (unsigned i = 0; i < bookR_W.size(); i++)
			{
				if (reader.readerbook[key3 - 1].m_strBookName == bookR_W[i].m_strBookName && reader.readerbook[key3 - 1].m_iBookCode == bookR_W[i].m_iBookCode)//在book.txt 中找到用户还的那本书
				{
					bookR_W[i].m_iBookCount++;
				}
			}

			if ((reader.readerbook.begin() + key3 - 1) != reader.readerbook.end())
			{
				reader.readerbook.erase(reader.readerbook.begin() + key3 - 1);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				reader.readerbook.pop_back();//如果要删除的是最后一个元组的话
			}
			reader.ReduceCount();//用户的借书总量减少一本

			ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
			file1.close();
			Write("book.txt", bookR_W);//写入book.txt文件

			//将reader即修改后的单个用户信息更新流中相应的用户信息
			teacher_reader.insert(teacher_reader.begin() + key5, reader);//在流的指定位置插入数据
			//将修改的信息写入ReaderInfo.txt
			ofstream file2(filename, ios::trunc | ios::out);//将文件清空以便重新写入
			file2.close();
			Write(filename, teacher_reader);//写入文件				

			cout << "是否继续归还,是请按1，否则按任意键退出" << endl;
			cin >> key4;
			if (key4 == "1" && reader.readerbook.size() > 0)//当此用户还有书，且确认继续归还时
				continue;
			else
			{
				cout << "还书成功" << endl;
				break;//退出内层while
			}
		}
		if (key4 != "1")
		{
			break;//退出外层while
		}
	}
}

void library::Return(Student_Reader reader, string filename)
{
	//1、读取读者信息（不显示）
	//2、匹配用户名或ID
	//3、显示借书信息
	//4、选择要还图书
	//5、修改读者信息
	//6、修改文件信息

	vector<Student_Reader> student_reader(Read<Student_Reader>(filename));
	while (true)
	{
		string name;
		string key4;//判断是否继续还书vector<int>key7;//记录用户在vector流中的位置
		int key5;//记录用户在文件中的位置
		bool key2 = false;//判断用户是否存在
		for (unsigned i = 0; i < student_reader.size(); i++)
		{
			if (student_reader[i].putCode() == m_strRCode)//找到用户
			{
				key2 = true;
				reader = student_reader[i];
				//cout << "查询出的第 " << reader.size() << " 位用户" << endl;
				key5 = i;//记录用户在vector流中的位置
				student_reader[i].display();//输出用户信息
			}
		}

		//不存在此用户
		if (key2 == false)
		{
			cout << "此用户不存在，您还未借书" << endl;
			break;
		}
		if (reader.readerbook.size() < 1)
		{
			cout << "您还未借书" << endl;
			break;
		}

		//此用户存在,且有未还书
		else
		{
			cout << "请输入要归还的图书序号" << endl;
			int key3;
			cin >> key3;

			//将修改的信息写入Book.txt  和  ReaderInfo.txt
			vector<Book> bookR_W(Read<Book>("book.txt"));
			for (unsigned i = 0; i < bookR_W.size(); i++)
			{
				if (reader.readerbook[key3 - 1].m_strBookName == bookR_W[i].m_strBookName && reader.readerbook[key3 - 1].m_iBookCode == bookR_W[i].m_iBookCode)//在book.txt 中找到用户还的那本书
				{
					bookR_W[i].m_iBookCount++;
				}
			}

			if ((reader.readerbook.begin() + key3 - 1) != reader.readerbook.end())
			{
				reader.readerbook.erase(reader.readerbook.begin() + key3 - 1);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				reader.readerbook.pop_back();//如果要删除的是最后一个元组的话
			}
			reader.ReduceCount();//用户的借书总量减少一本

			ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
			file1.close();
			Write("book.txt", bookR_W);//写入book.txt文件

			//将reader即修改后的单个用户信息更新流中相应的用户信息
			student_reader.insert(student_reader.begin() + key5, reader);//在流的指定位置插入数据
			//将修改的信息写入ReaderInfo.txt
			ofstream file2(filename, ios::trunc | ios::out);//将文件清空以便重新写入
			file2.close();
			Write(filename, student_reader);//写入文件				

			cout << "是否继续归还,是请按1，否则按任意键退出" << endl;
			cin >> key4;
			if (key4 == "1" && reader.readerbook.size() > 0)//当此用户还有书，且确认继续归还时
				continue;
			else
			{
				cout << "还书成功" << endl;
				break;//退出内层while
			}
		}
		if (key4 != "1")
		{
			break;//退出外层while
		}
	}
}

void library::Return(Outside_campus_Reader reader, string filename)
{
	//1、读取读者信息（不显示）
	//2、匹配用户名或ID
	//3、显示借书信息
	//4、选择要还图书
	//5、修改读者信息
	//6、修改文件信息

	vector<Outside_campus_Reader> outside_campus_reader(Read<Outside_campus_Reader>(filename));
	while (true)
	{
		string name;
		string key4;//判断是否继续还书vector<int>key7;//记录用户在vector流中的位置
		int key5;//记录用户在文件中的位置
		bool key2 = false;//判断用户是否存在
		for (unsigned i = 0; i < outside_campus_reader.size(); i++)
		{
			if (outside_campus_reader[i].putCode() == m_strRCode)//找到用户
			{
				key2 = true;
				reader = outside_campus_reader[i];
				//cout << "查询出的第 " << reader.size() << " 位用户" << endl;
				key5 = i;//记录用户在vector流中的位置
				outside_campus_reader[i].display();//输出用户信息
			}
		}

		//不存在此用户
		if (key2 == false)
		{
			cout << "此用户不存在，您还未借书" << endl;
			break;
		}
		if (reader.readerbook.size() < 1)
		{
			cout << "您还未借书" << endl;
			break;
		}

		//此用户存在,且有未还书
		else
		{
			cout << "请输入要归还的图书序号" << endl;
			int key3;
			cin >> key3;

			//将修改的信息写入Book.txt  和  ReaderInfo.txt
			vector<Book> bookR_W(Read<Book>("book.txt"));
			for (unsigned i = 0; i < bookR_W.size(); i++)
			{
				if (reader.readerbook[key3 - 1].m_strBookName == bookR_W[i].m_strBookName && reader.readerbook[key3 - 1].m_iBookCode == bookR_W[i].m_iBookCode)//在book.txt 中找到用户还的那本书
				{
					bookR_W[i].m_iBookCount++;
				}
			}

			if ((reader.readerbook.begin() + key3 - 1) != reader.readerbook.end())
			{
				reader.readerbook.erase(reader.readerbook.begin() + key3 - 1);//后面元素自动向前移动，且数组长度自动减小,但不能是vector的最后一个元组
			}
			else
			{
				reader.readerbook.pop_back();//如果要删除的是最后一个元组的话
			}
			reader.ReduceCount();//用户的借书总量减少一本

			ofstream file1("book.txt", ios::trunc | ios::out);//将文件清空以便重新写入
			file1.close();
			Write("book.txt", bookR_W);//写入book.txt文件

			//将reader即修改后的单个用户信息更新流中相应的用户信息
			outside_campus_reader.insert(outside_campus_reader.begin() + key5, reader);//在流的指定位置插入数据
			//将修改的信息写入ReaderInfo.txt
			ofstream file2(filename, ios::trunc | ios::out);//将文件清空以便重新写入
			file2.close();
			Write(filename, outside_campus_reader);//写入文件				

			cout << "是否继续归还,是请按1，否则按任意键退出" << endl;
			cin >> key4;
			if (key4 == "1" && reader.readerbook.size() > 0)//当此用户还有书，且确认继续归还时
				continue;
			else
			{
				cout << "还书成功" << endl;
				break;//退出内层while
			}
		}
		if (key4 != "1")
		{
			break;//退出外层while
		}
	}
}

void library::borrowtype(int chiose1)
{
	switch (chiose1)
	{
	case 1:
	{
		Teacher_Reader reader;
		borrow(reader, "Teacher_Reader.txt");
		break;
	}
	case 2:
	{
		Student_Reader reader;
		borrow(reader, "Student_Reader.txt");
		break;
	}
	case 3:
	{
		Outside_campus_Reader reader;
		borrow(reader, "Outside_campus_Reader.txt");
		break;
	}
	default:
		break;
	}
}

void library::returntype(int chiose2)
{
	switch (chiose2)
	{
	case 1:
	{
		Teacher_Reader reader;
		Return(reader, "Teacher_Reader.txt");
		break;
	}
	case 2:
	{
		Student_Reader reader;
		Return(reader, "Student_Reader.txt");
		break;
	}
	case 3:
	{
		Outside_campus_Reader reader;
		Return(reader, "Outside_campus_Reader.txt");
		break;
	}
	default:
		break;
	}
}



