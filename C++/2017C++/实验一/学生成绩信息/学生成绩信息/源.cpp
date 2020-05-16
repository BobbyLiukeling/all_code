/*
u	实验目的和要求
掌握函数的定义、申明；掌握函数的调用方法；熟练掌握指针、地址、指针类型、空指针等有关概念；
熟练掌握指针的间接访问、指针的加减运算和指针表达式；学会使用指针变量访问数组元素;学会建立动态数组的方法。
u	主要实验方法
编写一个程序，该程序提示用户输入学生的姓名及考试分数（假定每个班级学生人数最多为30人），并完成下列功能：
①输出班级平均分；
②输出最高、低分及最高、低分学生的姓名，低分学生姓名加密输出；
③对于人数有变化的情况，应使用动态数组。
*/

#include<iostream>
#include<string>
using namespace std;
const int num = 2;


struct Student
{
	string name;
	float score;
};

void GetStudent(Student *p)//获取学生信息
{
	for (int i = 0; i < num; i++)
	{
		cout << "please input the no." << i + 1 << " name " << endl;
		cin >> p->name;
		cout << "please input the no." << i + 1 << "score " << endl;
		cin >> p->score;
		p++;
	}
}

void Average(Student *p)//求平均数
{
	float average = 0, amount = 0;
	for (int i = 0; i < num; i++)
	{
		amount += p->score;
		p++;
	}
	average = amount / num;
	cout << "the average is  " << average << endl;
}

void maxScore(Student *p)//最大值
{
	float a1=p->score;
	Student *p1 = p;
	for (int i = 0; i < num-1; i++)
	{
		p++;
		if (a1 < p->score)
		{
			a1 = p->score;
			p1 = p;
		}
		
	}
	cout << "the top score is  " << p1->score << "    and the student is  " << p1->name << endl;
}

void minScore(Student *p)//最小值
{
	float a2=p->score;
	Student *p2 = p;
	for (int i = 0; i < num-1; i++)
	{
		p++;
		if (a2 >p->score)
		{
			a2 = p->score;
			p2 = p;
		}	
	}
	cout << "the minimum score is  " << a2 << "    and the student is" << "******" << endl;
}

int main()
{
	Student *p = new Student;
	Student *t = p;

	GetStudent(p);//输入成绩

	p = t;//平均值
	Average(p);

	p = t;//最大值
	maxScore(p);

	p = t;//最小值
	minScore(p);

	delete p;

	cout << "按任意键退出......" << endl;
	getchar();
}
