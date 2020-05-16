#ifndef MATRIX_H_
#define MATRIX_H_

class matrix
{
public:
	matrix();
	matrix(int l, int w);
	matrix operator+(matrix &m1);
	void putmatrix();//Êä³ö¾ØÕó
	~matrix();
private:
	
	int length;
	int width;
	int **a;
};

#endif

