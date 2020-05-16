class Array
{
public:
	Array(int len);
	~Array();
	void setLen(int len);
	int getLen();
	Array& printInfo();
private:
	int m_iLen;
};