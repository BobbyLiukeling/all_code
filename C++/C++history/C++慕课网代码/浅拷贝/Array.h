class Array
{
public:
	Array();
	Array(const Array &arr);
	~Array();
	void setCount(int count);
	int getCount();
	void printAddr();
private:
	int m_iCount;
	int *m_pArr;
};