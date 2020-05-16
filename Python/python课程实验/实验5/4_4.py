# -*- coding:utf-8 -*-
"""
@author:liukeling
@file:4_4.py
@time:2018/10/18 13:49,jinzhita
"""

n=int(input('plaese input n:'))

t=1

for i in range(n):
    for j in range(int(n-i-1)):
        print(' ',end='')
    for k in range(i+1):
        print('{n:3} '.format(n=t),end='')
        t+=1
    print()