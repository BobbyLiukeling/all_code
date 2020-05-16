path = "C:\\Users\\qwert\\Desktop\\新建文本文档.txt"
import xlsxwriter

workbook = xlsxwriter.Workbook("English.xlsx")#创建一个工作表,注意Workbook的大小写
worksheet = workbook.add_worksheet()#创建一个工作表对象


def is_chinese(uchar):
    """判断一个unicode是否是汉字"""
    if uchar >= u'\u4e00' and uchar <= u'\u9fa5':
        return True
    else:
        return False


def is_alphabet(uchar):
    """判断一个unicode是否是英文字母"""
    if (uchar >= u'\u0041' and uchar <= u'\u005a') or (uchar >= u'\u0061' and uchar <= u'\u007a'):
        return True
    else:
        return False


f = open(path)  # 返回一个文件对象
line = f.readline()  # 调用文件的 readline()方法
count = 0
while line:
    try:
        line = line[line.index('.')+1:].strip()
    except:
        pass
    if(is_alphabet(line[0]) == False):
        pass
    else:#是单词
        print(line),  # 后面跟 ',' 将忽略换行符
        line = line[:-3].strip()
        chi = ''
        eng = ''
        s = 0
        for i in line[::-1]:
            if(is_chinese(i) == True or i in (",","…","、","(",")","，"," ","·",";","/")):
                chi = i+chi
                s = s+1
            else:
                break
        eng = line[:-s].split("[")[0]
        worksheet.write(count,0,eng)#位置：A3
        try:#可能是短句没有中文
            worksheet.write(count,1,chi)#位置：A4
        except:
            pass
        count = count + 1
    line = f.readline()

f.close()
workbook.close()


# import xlsxwriter
#
# workbook=xlsxwriter.Workbook("demo.xlsx")#创建一个工作表,注意Workbook的大小写
# worksheet=workbook.add_worksheet()#创建一个工作表对象
#
# worksheet.set_column("A:A",20)#设置第一行的宽度为20px
# worksheet.write("A1","hello world")#将数据写入单元格，位置是A1
# worksheet.write("A2","python")
#
# #第二种将数据写入单元格方法
# worksheet.write(2,0,123)#位置：A3
# worksheet.write(3,0,231)#位置：A4
# worksheet.write(4,0,"=SUM(A3:A4)")#求和并写入
#
# #写入图片
# worksheet.insert_image("A5","img1.jpg")
# workbook.close()



# def is_chinese(uchar):
#     """判断一个unicode是否是汉字"""
#     if uchar >= u'\u4e00' and uchar <= u'\u9fa5':
#         return True
#     else:
#         return False
#
# a = 'Northern北部'
# chi = ''
# eng = ''
# s = 0
# for i in a[::-1]:
#     if(is_chinese(i) == True):
#         chi = i+chi
#         s = s+1
#     else:
#         break
# eng = a[:-s]
# print(chi)
# print(eng)