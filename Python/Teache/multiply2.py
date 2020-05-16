class Multiply:
    def __init__(self):
        self.pre = 4#设置全局精度精度取小数点后六位二进制

    # def dTob(self,n):
    #     n = int(n)
    #     if abs(n)>2**self.pre-1|abs(n)<1:
    #         print(str(n)+" 不是正确输入，请输入绝对值在1到64之间的整数")
    #         return
    #
    #
    #     #判断符号位
    #     if n<0:
    #         sign = 1
    #         n=-n
    #         a = 1
    #     else:
    #         sign = 0
    #
    #     numberinfo = []
    #     numberinfo.append(str(sign))
    #     '''
    #     把一个带小数的十进制数n转换成二进制
    #     小数点后面保留self.pre位小数
    #     '''
    #
    #     # decimal = float(n)
    #     # i = 0
    #     # decimal_convert=''
    #     # while decimal != 0 and i < self.pre:
    #     #     result = int(decimal * 2)
    #     #     decimal = decimal * 2 - result
    #     #     decimal_convert = decimal_convert + str(result)
    #     #     number = decimal_convert
    #     #     i = i + 1
    #     number = bin(n)[2:]
    #     numberinfo.append((number)[0: self.pre].rjust(self.pre, '0'))  # 保留六位位数，不足的用0补足
    #     return numberinfo
    def dTob(self,n):
        n = str(n)

        # print(n+'   fgnm,.')
        # for i in n:
        #     if (i!='-')|(i!='1')|(i!='0'):
        #     # if i!='-':
        #         print(str(n) + " lallal不是正确输入，输入一个正确格式的二进制数，形如：-0101")
        #         return
        key='-01'
        for i in n:
            if (i in key)==False:
                print(str(n) + " lallal不是正确输入，输入一个正确格式的二进制数，形如：-0101")
                return


        if '-' in n==True & n.startswith('-')==False:
            print(str(n) + " 不是正确输入，输入一个正确格式的二进制数，形如：-0101")
            return

        #判断符号位
        if n.startswith('-'):
            sign = 1
            n=-int(n)
            a = 1
        else:
            sign = 0

        numberinfo = []
        numberinfo.append(str(sign))
        numberinfo.append((str(n))[0: self.pre].rjust(self.pre, '0'))  # 保留六位位数，不足的用0补足
        return numberinfo


    def get_complement(self,list):#补码
        if int(list[0])==1:#负数
            pattern = 2**len(list[1])#模长
            complement = bin(pattern-int(list[1],2))[2:].rjust(self.pre,'0')#负数的补码,最后写为四位 , r 为原来数的位置
            list[1] = complement

        #将除数和被除数不足为六位
        return list

    def do_convert(self,list):#[-x]补
        if int(list[0])==0:#原码为正
            list[0] = '1'
            pattern = 2**len(list[1])#模长
            complement = bin(pattern-int(list[1],2))[2:].rjust(self.pre,'0')#负数的补码,最后写为四位 , r 为原来数的位置
            list[1] = complement
        elif int(list[0])==1:#原码为负
            list[0] = '0'

        #将除数和被除数不足为四位
        return list



    def get_string_multiply(self,list):
        if list[0] == '0':
            list[1] = '00'+list[1]
        elif list[0] == '1':
            list[1] = '11'+list[1]
        return list


    def get_string_multipier(self,list):#乘数
        if list[0] == '0':
            list[1] = '0'+list[1] + '0'
        elif list[0] == '1':
            list[1] = '1' + list[1]+'0'
        return list

    def demo(self,X,Y):
        # X = input('请输入被乘数')
        # Y = input('请输入乘数')
        # X = -3
        # Y =2
        Q = self.dTob(X)
        N = self.dTob(Y)
        print(str(X)+' 被乘数原码为：' +Q[0]+ ' '+ Q[1])
        print(str(Y)+' 乘数原码为：' + N[0]+' '+N[1])
        #变补，及补数
        A = self.get_complement(self.dTob(X))
        B = self.do_convert(self.dTob(X))#变补
        C = self.get_complement(self.dTob(Y))
        print('被乘数补码为：'+A[0]+' '+A[1])
        print('被乘数的负数补码为： '+B[0]+' '+B[1])
        print('乘数原码为：'+C[0]+' '+C[1])
        #添位
        A = self.get_string_multiply(A)
        B = self.get_string_multiply(B)
        C = self.get_string_multipier(C) #前面添位


        T = '000000'
        count = len(A[1])#度量

        while True:#注意加法会溢出
            H = int(C[1][-1])-int(C[1][-2])
            if H == -1:
                s = bin(int(T,2)+int(B[1],2))
                #[2:]：去掉0b   [-6:]：防止溢出，去掉高位符号位,ljust(6,'0'):低位不足用0添上
                T = bin(int(T,2)+int(B[1],2))[2:].rjust((self.pre+2),'0')
                T = T[-(self.pre+2):]
            elif H == 1:
                T = bin(int(T,2)+int(A[1],2))[2:].rjust((self.pre+2),'0')
                T = T[-(self.pre+2):]
            elif H == 0:
                T = T

            count = count - 1
            if count>1:
                C[1] = (T[-1]+C[1])[0:(self.pre+2)]#右移并将结果的尾数加到首部
                temp = T[0]
                T = (temp+T)[0:(self.pre+2)]
            elif count == 1:#最后一步
                T = T+C[1] #最后结果，未化解
                break


        result = T[1:]
        result = (result[0]+'.'+result[1:])[0:(self.pre*2+2)]
        # result = result[:result.rindex('1')+1]
        print('最后计算结果的为补码： '+result )


if __name__ == "__main__":
    # X = input("请输入二进制乘数：")
    # Y= input('请输入二进制被乘数：')
    M = Multiply()
    X = -1101
    Y = 1011
    M.demo(X,Y)











