#include<iostream>
#include"Worker.h"
using namespace std;

Worker::Worker()
{
	cout << "Worker()" << endl;
}

Worker::~Worker()
{
	cout << "~Worker()" << endl;
}

void Worker::work()
{
	m_strName = "Tom";
	cout << "m_strName:" << m_strName << endl;

	cout << "work()" << endl;
}

 