#ifndef _TIME_H
#define _TIME_H

#include<iostream>
using namespace std;

class Match;
class Time
{
	friend Match;
public:
	Time();
	~Time();
	Time(int hour, int minute, int second);
private:
	int m_iHour;
	int m_iMinute;
	int m_iSecond;
	void printTime();
};

Time::Time()
{
}

Time::~Time()
{
}

Time::Time(int hour, int minute, int second)
{
	m_iHour = hour;
	m_iMinute = minute;
	m_iSecond = second;
}

void Time::printTime()
{
	cout << m_iHour<< "Ê±"<<m_iMinute << "·Ö"<<m_iSecond<<"Ãë"<< endl;
}
#endif