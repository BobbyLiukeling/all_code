# -*- coding:utf-8 -*-
"""
@author:liukeling
@file:shixun2.py
@time:2018/10/18 13:58
"""

"""
5

123
asd
0.123
fger
/'213
"""

intCount=0
strCount=0
otherCount=0

n=int(input('n of string:'))

for i in range(n):
    t=input()

    if t.isdigit():
        intCount+=1
    elif t.isalpha():
        strCount+=1
    else:
        otherCount+=1

print(intCount)
print(strCount)
print(otherCount)