# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:3_2.py
@time:2018/10/10 16:34
"""


if __name__ == "__main__":
    list=[110,'dog','cat',120,'apple']

    list.insert(2,[])

    list.pop(5)

    for i in list:
        if type(i)==int:
            print(i,i*10)

    print(list)