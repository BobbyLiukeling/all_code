//#include<iostream>
//#include"MyArray.h"
//
//using namespace std;
//
//template<typename T,int kise,int kval>
//MyArray<T, kise, kval>::MyArray()
//{
//	m_pArr = new T[kise];
//	for (int i = 0; i < kise; i++)
//	{
//		m_pArr[i] = kval;
//	}
//}
//
//template<typename T, int kise, int kval>
//MyArray<T, kise, kval>::~MyArray()
//{
//	delete[]m_pArr;
//	m_pArr = NULL;
//}
//
//
//template<typename T, int kise, int kval>
//void MyArray<T, kise, kval>::diaplay()
//{
//	for (int i = 0; i < kise; i++)
//	{
//		cout << m_pArr[i] << endl;
//	}
//}