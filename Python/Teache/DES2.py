class Text:
    def __init__(self):
        self.pre = 4


    def Dstanderd(self,n):
        n = str(n)

        key='-01'
        for i in n:
            if (i in key)==False:
                print(str(n) + "输入不正确")
                return


        if '-' in n==True & n.startswith('-')==False:
            print(str(n) + " 输入不正确")
            return

        if n.startswith('-'):
            sign = 1
            n=-int(n)
            a = 1
        else:
            sign = 0

        numberinfo = []
        numberinfo.append(str(sign))
        numberinfo.append((str(n))[0: self.pre].rjust(self.pre, '0'))
        return numberinfo


    def complement(self,list):#补码
        if int(list[0])==1:#负数
            pattern = 2**len(list[1])#模长
            complement = bin(pattern-int(list[1],2))[2:].rjust(self.pre,'0')
            list[1] = complement

        return list

    def convert(self,list):#[-x]补
        if int(list[0])==0:#原码为正
            list[0] = '1'
            pattern = 2**len(list[1])#模长
            complement = bin(pattern-int(list[1],2))[2:].rjust(self.pre,'0')
            list[1] = complement
        elif int(list[0])==1:#原码为负
            list[0] = '0'

        return list



    def multiply(self,list):
        if list[0] == '0':
            list[1] = '00'+list[1]
        elif list[0] == '1':
            list[1] = '11'+list[1]
        return list


    def multipier(self,list):#乘数
        if list[0] == '0':
            list[1] = '0'+list[1] + '0'
        elif list[0] == '1':
            list[1] = '1' + list[1]+'0'
        return list

    def demo(self,X,Y):
        Q = self.Dstanderd(X)
        N = self.Dstanderd(Y)
        A = self.complement(self.Dstanderd(X))
        B = self.convert(self.Dstanderd(X))#变补
        C = self.complement(self.Dstanderd(Y))
        print(str(X) + ' 被乘数原码：' + Q[0] + ' ' + Q[1])
        print(str(Y) + ' 乘数原码：' + N[0] + ' ' + N[1])
        print('被乘数补码：'+A[0]+' '+A[1])
        print('被乘数的负数补码： '+B[0]+' '+B[1])
        print('乘数原码：'+C[0]+' '+C[1])
        #添位
        A = self.multiply(A)
        B = self.multiply(B)
        C = self.multipier(C) #前面添位

        T = '000000'
        count = len(A[1])#度量

        while True:#注意加法会溢出
            H = int(C[1][-1])-int(C[1][-2])
            if H == -1:
                s = bin(int(T,2)+int(B[1],2))
                T = bin(int(T,2)+int(B[1],2))[2:].rjust((self.pre+2),'0')
                T = T[-(self.pre+2):]
            elif H == 1:
                T = bin(int(T,2)+int(A[1],2))[2:].rjust((self.pre+2),'0')
                T = T[-(self.pre+2):]
            elif H == 0:
                T = T

            count = count - 1
            if count>1:
                C[1] = (T[-1]+C[1])[0:(self.pre+2)]
                temp = T[0]
                T = (temp+T)[0:(self.pre+2)]
            elif count == 1:
                T = T+C[1]
                break


        result = T[1:]
        result = (result[0]+'.'+result[1:])[0:(self.pre*2+2)]
        # result = result[:result.rindex('1')+1]
        print('计算结果： '+result )


if __name__ == "__main__":
    X = input("输入乘数：")
    Y= input('输入被乘数：')
    M = Text()
    M.demo(X,Y)











