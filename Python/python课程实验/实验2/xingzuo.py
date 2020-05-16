# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:xingzuo.py
@time:2018/10/9 11:06
"""

if __name__ == "__main__":
    ls = ["白羊", "金牛", "天蝎", "摩羯", "处女", "双鱼", "水瓶", "狮子", "射手"]

    name=input('请输入名字：')

    for i in range(len(ls)):
        print("{index}:{xz}".format(index=i+1,xz=ls[i]))

    xingzuo=int(input('请根据编号选择您的星座:'))

    print("{name} 你的星座是 {xz}".format(name=name,xz=ls[xingzuo-1]))