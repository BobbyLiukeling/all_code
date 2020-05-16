# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:3_4.py
@time:2018/10/10 16:34
"""


if __name__ == "__main__":
    dict={'Math':96,'English':86,'Chinese':95.5,'Biology':86,'Physics':None}

    dict["History"]=88

    dict.pop('Physics')

    t=int(dict['Chinese'])
    if dict['Chinese']-int(dict['Chinese'])>=0.5:
        t+=1
    dict['Chinese']=t

    print(dict['Math'])

    print(dict)