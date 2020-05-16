# import os
# names = os.listdir('F:/学习/PDF')  #路径
# i=0  #用于统计文件数量是否正确，不会写到文件里
# train_val = open('test.txt','w')
# for name in names:
#     index = name.rfind('.')
#     name = name[:index]
#     train_val.write(name+'\n')
#     print(name)
#     i=i+1
# print(i)
# s =''
# for i in range(400,500):
#     s =s+'.'+'{}'.format(i)
# print(s)
#
#
#
# s = s.split('.')
# print(s)
# for i in s:
#     i = i+'.txt'
#     open(i,'w')

import os,pdb
# def file_name(file_dir):
#     for root, dirs, files in os.walk(file_dir):
#         print('root_dir:', root)  # 当前目录路径
#         print('sub_dirs:', dirs)  # 当前路径下所有子目录
#         print('files:', files)  # 当前路径下所有非目录子文件
#         print("*"*20)
#         for i in files:
#             print (i)
def file_name(file_dir):
    for root, dirs, files in os.walk(file_dir):
        # pdb.set_trace()
        print('*******root_dir:', root)  # 当前目录路径

        s1 = root.split("\\")[-1]
        # print('files:', files)  # 当前路径下所有非目录子文件
        # print("*"*20)
        if (s1 != '严蔚敏《数据结构》的全部代码实现（C语言）'):
            date = open("date1.txt",'a')
            date.write(root + '\n')
            for j in files[1:]:
                # pdb.set_trace()
                # for j in i:
                s2  = j.split(".")[-1]
                # pdb.set_trace()
                if(s2 in ['c','C','H','h']):
                    with open(root+'\\'+j) as f:  # 默认模式为‘r’，只读模式

                        contents = f.readlines()[0]
                        # contents1 = f.readline()
                        # pdb.set_trace()
                        date.write(j+"----------")
                        date.write(contents.split("*")[1] + '\n')

                        # date.write(contents + '\n')
                        f.close()

            date.close()



file_name('F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）')