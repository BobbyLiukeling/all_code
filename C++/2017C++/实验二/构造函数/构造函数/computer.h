#include<iostream>
#include<string>
using namespace std;

class Computer
{
public:
	Computer(string model,int price );
	~Computer();
	void put_name();
private:
	string Strmodel;
	int Iprice;
};