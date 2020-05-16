# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:yuanzhoulv.py
@time:2018/10/9 11:00
"""
import math

pi=3.14

def sanjiao_area(a,b,c):
    p = (a + b + c) / 2.0
    return math.sqrt(p*(p-a)*(p-b)*(p-c))

def yuan_area(r):
    return r*r*pi

if __name__ == "__main__":
    a, b, c = input("please input a,b,c:").split()
    a=int(a)
    b=int(b)
    c=int(c)
    print("sanjiao area is:",sanjiao_area(a,b,c))

    r=float(input('please input R:'))
    print("yuan area is: {s:0.3f}\nC is:{c}\n R is:{r}".format(r=r,c=2*pi*r,s=yuan_area(r)))