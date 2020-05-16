#
# n=int(input('plaese input n:'))
#
# t=1
#
# for i in range(n):
#     for j in range(int(n-i-1)):
#         print(' ',end='')
#     for k in range(i+1):
#         print('{n:3} '.format(n=t),end='')
#         t+=1
#     print()

# def fun(x):
#     sum=0
#     for i in x:
#         sum+=i
#     return sum
#
# if __name__ == "__main__":
#     num=[[1,2,3],[4,5,6],[7,8.9]]
#
#     l1=[]
#     l2=[]
#
#     for i in num:
#         l1.append(fun(i))
#
#     fun2=lambda x:fun(x)
#     l2=list(map(fun2,num))
#
#     print(l1)
#     print(l2)



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
