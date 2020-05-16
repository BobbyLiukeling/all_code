import pdb
import math
import random

class constellation:
    def get_constellation(self,month, date):
        dates = [21, 20, 21, 21, 22, 22, 23, 24, 24, 24, 23, 22]
        constellations = ["摩羯", "水瓶", "双鱼", "白羊", "金牛", "双子", "巨蟹", "狮子", "处女", "天秤", "天蝎", "射手", "摩羯"]
        if date < dates[month-1]:
            return constellations[month-1]
        else:
            return constellations[month]

    def do_constellation(self):
        name = input("请输入您的名字：")
        mouth = int(input("请输入您的出生月份：")) % 12
        day = int(input("请输入您的出生日期：")) % 30
        print(name + "您的星座是：" + self.get_constellation(mouth, day))


class circular:
    def demo(self):
        print("1、如果需要输入半径计算周长请输入1；\n 2、如果需要输入周长计算半径请输入2；\n "
              "3、如果需要输入面积计算半径请输入3")
        chiose = input("please input parameter of cricle:")
        try:
            chiose = int(chiose)
            if chiose in (1,2,3):
                if chiose == 1:
                    self.get_circular()
                elif chiose == 2:
                    self.by_perimeter()
                elif chiose == 3:
                    self.by_area()
            else:
                print("请输入正确序号")
        except Exception as e:
            print(e)
            print("请输入正确序号")
            pass


    def get_circular(self):
        radius = input("please input radius of cricle:")
        radius = int(radius)
        circumference = 2 * math.pi * radius
        area=math.pi*radius*radius
        print ( "circumference of circle:{0}".format(round(circumference,2)))
        print ( "area of cricle:{}".format(round(area,2)))

    def by_perimeter(self):
        length = input("please input length of cricle:")
        length = int(length)
        radius = length/2/math.pi
        print("radius of circle divide by length:{0}".format(round(radius, 2)))

    def by_area(self):
        area = input("please input area of cricle:")
        area = int(area)
        radius = math.sqrt(area)
        print("radius of circle divide by area:{0}".format(round(radius, 2)))


class do_sort:
    def __init__(self):
        self.List = [random.randint(0,100) for i in range(10)]

    def demo(self):
        _str = input('请输入一个要排序的整数：')
        self.List.append(int(_str))
        new_list = sorted(self.List)
        print(new_list)


if __name__ == '__main__':
    #星座
    constellation = constellation()
    constellation.do_constellation()

    #圆
    cir = circular()
    cir.demo()

    #排序
    s = do_sort()
    print('原列表是：', s.List)
    s.demo()






