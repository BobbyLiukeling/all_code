class Array
{
public:
	Array(int count);//默认构造函数
	Array(const Array &arr);//拷贝构造函数
	~Array();//析构函数
	void setCount(int count);
	int getCount();
	void printAddr();//打印指针m_pArr的值
private:
	int m_iCount;
	int *m_pArr;
};