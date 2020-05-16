#ifndef _MATCH_H
#define _MATCH_H

#include<iostream>
#include"Time.h"

using namespace std;

class Match
{
public:
	Match();
	~Match();
	Match(int hour, int minute, int sec) :m_tTime(hour, minute, sec){}
	void testTime();
private:
	Time m_tTime;
};

Match::Match()
{
}

Match::~Match()
{
}

void Match::testTime()
{
	//m_tTime.printTime();
	cout << m_tTime.m_iHour << ":" << m_tTime.m_iMinute << ":" << m_tTime.m_iSecond << endl;
}
#endif