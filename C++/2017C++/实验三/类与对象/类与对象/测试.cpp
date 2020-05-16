#include<iostream>
using namespace std;

class array
{
private:
	int arr[2][3];
public:
	array()      //³õÊ¼»¯Îª0
	{
		int i, j;
		for (i = 0; i<2; i++)
		{
			for (j = 0; j<3; j++)
			{
				arr[i][j] = 0;
			}
		}
	}
	array(int **a)
	{
		arr = a;
	}
	array operator + (const array &a);
};

array array::operator + (const array &a)
{
	int i, j;
	array c;
	for (j = 0; j<2; j++)
	{
		for (i = 0; i<3; i++)
		{
			c.arr[j][i] = arr[j][i] + a.arr[j][i];
		}
	}
	return c;
}

int main()
{
	int i, j;
	int a[2][3] = { { 2, 5, 10 }, { 4, 1, 9 } };
	int b[2][3] = { { 3, 7, 9 }, { 2, 9, 12 } };
	int c[2][3] = { 0 };
	array ay(a);
	c = a + b;
	for (i = 0; i<2; i++)
	{
		for (j = 0; j<3; j++)
		{
			cout << c[i][j] << " " << endl;;
		}
	}
	return 0;
}



#include <initializer_list>
#include <algorithm>
#include <functional>

template<typename T, size_t D0, size_t... DN>
struct matrix
{
	typedef matrix<T, DN...> elem_type;
	matrix() = default;
	matrix(std::initializer_list<elem_type> l)
	{
		std::copy(std::begin(l), std::end(l), data_);
	}
	matrix operator+(const matrix& m) const
	{
		matrix result;
		std::transform(data_, data_ + D0, m.data_, result.data_, std::plus<elem_type>());
		return result;
	}
	const elem_type& operator[](size_t index) const
	{
		return data_[index];
	}
	elem_type& operator[](size_t index)
	{
		return data_[index];
	}
private:
	elem_type data_[D0];
};

template<typename T, size_t D0>
struct matrix<T, D0>
{
	typedef T elem_type;
	matrix() = default;
	matrix(std::initializer_list<elem_type> l)
	{
		std::copy(std::begin(l), std::end(l), data_);
	}
	matrix operator+(const matrix& m) const
	{
		matrix result;
		std::transform(data_, data_ + D0, m.data_, result.data_, std::plus<elem_type>());
		return result;
	}
	const elem_type& operator[](size_t index) const
	{
		return data_[index];
	}
	elem_type& operator[](size_t index)
	{
		return data_[index];
	}
private:
	elem_type data_[D0] = {};
};

#include <iostream>
using namespace std;

template<typename T, size_t R, size_t C>
void Print2D(const matrix<T, R, C>& m)
{
	for (size_t r = 0; r != R; ++r)
	{
		for (size_t c = 0; c != C; ++c)
			cout << m[r][c] << ", ";
		cout << '\n';
	}
}

int main(void)
{
	using mtx_int_2_3 = matrix<int, 2, 3>;

	mtx_int_2_3 a = { { 2, 5, 10 }, { 4, 1, 9 } };
	mtx_int_2_3 b = { { 3, 7, 9 }, { 2, 9, 12 } };
	mtx_int_2_3 c = a + b;

	Print2D(a);
	cout << "------------------\n";
	Print2D(b);
	cout << "------------------\n";
	Print2D(c);

	return 0;
}