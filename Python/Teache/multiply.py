from decimal import Decimal
import pdb

def dTob(n, pre=6):
    #符号位
    n = float(n)
    if n<0:
        sign = 1
        n=-n
        a = 1
    else:
        sign = 0

    numberinfo = []
    numberinfo.append(str(sign))
    '''
    把一个带小数的十进制数n转换成二进制
    小数点后面保留self.pre位小数
    '''
    string_number1 = str(n)  # number1 表示十进制数，number2表示二进制数

    flag = False
    try:#判断是否为小数
        string_number1.index('.')
        flag = True
    except:
        pass

    if flag:
        string_integer, string_decimal = string_number1.split('.')  # 分离整数部分和小数部分
        integer = int(string_integer)
        decimal = Decimal(str(n)) - integer



        string_integer = str(bin(integer))[2:]#整数部分转换成二进制字符串
        i = 0
        decimal_convert = ""
        while decimal != 0 and i < pre:
            result = int(decimal * 2)
            decimal = decimal * 2 - result
            decimal_convert = decimal_convert + str(result)
            i = i + 1
        if integer==0:
            numberinfo.append(0)#正数部分为0,小数点位置为0
            number = decimal_convert
        else:
            numberinfo.append(len(string_integer))#小数点位置
            number = string_integer + decimal_convert
        numberinfo.append((number)[0: 6].ljust(6, '0'))  # 保留四位数，不足的用0补足

    else:  # 若十进制只有整数部分
        string_number1 = bin(int(string_number1))#转换为二进制
        # return str(string_number1)[2:].ljust(7,'0')#装换为字符串
        numberinfo.append(len(str(string_number1)[2:]))
        numberinfo.append(str(string_number1)[2:8].ljust(6,'0'))#保留四位数，不足的用0补足

    return numberinfo


def get_complement(list):#补码
    if int(list[0])==1:#负数
        pattern = 2**len(list[2])#模长
        complement = bin(pattern-int(list[2],2))[2:].rjust(6,'0')#负数的补码,最后写为四位 , r 为原来数的位置
        list[2] = complement

    #将除数和被除数不足为四位
    return list

def do_convert(list):#[-x]补
    if int(list[0])==0:#原码为正
        list[0] = '1'
        pattern = 2**len(list[2])#模长
        complement = bin(pattern-int(list[2],2))[2:].rjust(6,'0')#负数的补码,最后写为四位 , r 为原来数的位置
        list[2] = complement
    elif int(list[0])==1:#原码为负
        list[0] = '0'

    #将除数和被除数不足为四位
    return list



def get_string_multiply(list):
    if list[0] == '0':
        list[2] = '00'+list[2]
    elif list[0] == '1':
        list[2] = '11'+list[2]
    return list


def get_string_multipier(list):#乘数
    if list[0] == '0':
        list[2] = '0'+list[2] + '0'
    elif list[0] == '1':
        list[2] = '1' + list[2]+'0'
    return list

def demo():
    # X = input('请输入被乘数')
    # Y = input('请输入乘数')
    X = 0.25
    Y =-0.125

    print(str(X)+' 被乘数原码为：' + dTob(X)[2])
    print(str(Y)+' 乘数原码为：' + dTob(Y)[2])
    #变补，及补数
    A = get_complement(dTob(X))
    B = do_convert(dTob(X))#变补
    C = get_complement(dTob(Y))
    print('被乘数补码为： '+A[2])
    print('被乘数的负数补码为： '+B[2])
    print('乘数原码为： '+C[2])
    #添位
    A = get_string_multiply(A)
    B = get_string_multiply(B)
    C = get_string_multipier(C) #前面添位


    T = '000000'
    count = len(A[2])#度量

    while True:#注意加法会溢出
        H = int(C[2][-1])-int(C[2][-2])
        if H == -1:
            s = bin(int(T,2)+int(B[2],2))
            #[2:]：去掉0b   [-6:]：防止溢出，去掉高位符号位,ljust(6,'0'):低位不足用0添上
            T = bin(int(T,2)+int(B[2],2))[2:].rjust(8,'0')
            T = T[-8:]
        elif H == 1:
            T = bin(int(T,2)+int(A[2],2))[2:].rjust(8,'0')
            T = T[-8:]
        elif H == 0:
            T = T


        count = count - 1
        if count>1:
            C[2] = (T[-1]+C[2])[0:8]#右移并将结果的尾数加到首部
            temp = T[0]
            T = (temp+T)[0:8]
        elif count == 1:#最后一步
            T = T+C[2] #最后结果，未化解
            break

    T = T[1:-2]#甩掉後面兩位，兩位符號位減掉一位
    point = A[1]+C[1]#符號位
    temp = T[point+1:]
    result = T[0:point+1]+'.'+T[point+1:]#最後結果
    # if result.startswith('00'):
    #     result = result[1:]
    # elif result.startswith('11'):
    #     result = result[1:]
    #去掉尾部多余0
    result = result[:result.rindex('1')+1]
    print('最后计算结果的为补码： '+result )


demo()











