#ifndef _MYARRAY_H
#define _MYARRAY_H

template<typename T,int kise,int kval>
class MyArray
{
public:
	MyArray();
	~MyArray()
	{
		delete []m_pArr;
		m_pArr = NULL;
	}
	void display();
private:
	T *m_pArr;
};



template<typename T, int kSize, int kValue>
void MyArray<T, kSize, kValue>::display()
{
	for (int i = 0; i < kSize; i++)
	{
		cout << m_pArr[i] << endl;
	}

}



template <typename T,int kise,int kval>
void MyArray<T, kise, kval >::display()
{
	for (int i = 0; i < kise; i++)
	{
		cout << m_pArr << endl;
	}
}


#endif