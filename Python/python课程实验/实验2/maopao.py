# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:maopao.py
@time:2018/10/9 10:55
"""


def maopao(list):
    for i in range(len(list)):
        for j in range(i + 1, len(list)):
            if list[i] > list[j]:
                list[i], list[j] = list[j], list[i]

if __name__ == "__main__":

    num=[9,8,7,6,5,4,3,2,1,0]

    maopao(num)

    print(num)
