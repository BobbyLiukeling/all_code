# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:3_5.py
@time:2018/10/17 16:13
"""

list1=['apple','pear','watermelon','peach']
list2=[]
list2.append('pear')
list2.append('banana')
list2.append('orange')
list2.append('peach')
list2.append('grape')

print(list1)
print(list2)

set1=set(list1)
set2=set(list2)

print(set1)
print(set2)

print('并集：',set.union(set1,set2))
print('交集：',set.intersection(set1,set1))
print('差集：',set.difference(set1,set2))