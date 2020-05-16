# -*- coding:utf-8 -*-
"""
@author:liukeling
@file:car.py
@time:2018/11/14 16:11
"""

class Car():

    def __init__(self,newWheelNum,newColor):
        print("这是一辆车")
        self.wheelNum=newWheelNum
        self.color=newColor

    def __del__(self):
        print("--析构函数被调用--")

    def run(self):
        print("车载跑，目标：夏威夷")

class Bus(Car):
    def __init__(self,newWheelNum,newColor):
        print("这是一辆巴士")
        self.wheelNum = newWheelNum
        self.color = newColor

    def __del__(self):
        print("--析构函数被调用--")

if __name__=="__main__":
    bus=Bus(6,'yellow')
    bus.run()
