# -*- coding:utf-8 -*-
"""
@author:liukeling
@file:5_2.py
@time:2018/10/24 16:04
添加列表
"""

def fun(x):
    sum=0
    for i in x:
        sum+=i
    return sum

if __name__ == "__main__":
    num=[[1,2,3],[4,5,6],[7,8.9]]

    l1=[]
    l2=[]

    for i in num:
        l1.append(fun(i))

    fun2=lambda x:fun(x)
    l2=list(map(fun2,num))

    print(l1)
    print(l2)