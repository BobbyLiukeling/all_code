# -*- coding:utf-8 -*-
"""
@author:liukeling
@file:shixun2.py
@time:2018/10/24 16:04
"""
if __name__ == "__main__":
    num=[1,2,3]

    fun2=lambda x:x**2
    l1=list(map(fun2,num))

    print(l1)