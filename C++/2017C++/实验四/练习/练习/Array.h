class Array
{
public:
	Array(int count);
	Array(const Array &arr);
	~Array();
	void setCount(int count);
	int getCount();
	/*void printArr();*/
	void print1();
private:
	int m_iCount;
	int *m_pArr;
};

