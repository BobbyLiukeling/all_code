#ifndef MATRIX_H_
#define MATRIX_H_


class matrix                                          //定义matrix类
{
public:
	matrix();                                          //默认构造函数
	matrix operator+(matrix &);        //重载运算符“+”
	friend matrix operator-( matrix &,matrix &);
	void input();                                      //输入数据函数
	void display();                                    //输出数据函数
private:
	int mat[2][3];
};

#endif

