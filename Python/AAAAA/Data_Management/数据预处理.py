# -*- encoding: utf-8 -*-
# @author : bobby
# @time : 2020/2/25 11:25
'''
数据预处理
'''


import pymysql
import xlsxwriter
import pdb
import pandas as pd
import numpy as np
import re
import jieba

from ..Text_Analysis.gerapy.projects.weibo.weibo.spiders.filmname import filmname # 前端传入的电影名



class Data_precess:

    def __init__(self):
        self.db = pymysql.connect(host="localhost", port=3306, user="root", passwd='867425', db="weibofilm",charset="utf8")
        # 使用 cursor() 方法创建一个游标对象 cursor
        self.cursor = self.db.cursor()

    def read(self): # weibo_essay
        '''
        将comment数据从数据库中读出
        :return:
        '''
        sql ="select id,comment_content from comment where lable = {}".format(filmname)
        # sql = 'select content from weibo_essay where id<500 '
        self.cursor.execute(sql)
        temp = self.cursor.fetchall()# 获取结果集列表
        return temp

    def Dict_to_csv(self,my_dict={}):
        workbook = xlsxwriter.Workbook('my_dict.xlsx')
        worksheet = workbook.add_worksheet()

        # 设定格式，等号左边格式名称自定义，字典中格式为指定选项
        # bold：加粗，num_format:数字格式
        i = 0
        for item in my_dict.items():
            # 行列表示法的单元格下标以0作为起始值，如‘3,0’等价于‘A3’
            worksheet.write(i, 0, item[0])  # 使用列行表示法写入数字‘123’
            worksheet.write(i, 1, item[1])  # 使用列行表示法写入数字‘456’
            i = i+1
        workbook.close()

    def data_to_csv(self,Dict = {}):
        df = pd.DataFrame(data=Dict,columns=['id','comment'])
        df = df.dropna()
        df = df.drop_duplicates(['comment']) #去重
        df.to_csv('comment.csv',encoding='utf-8',columns=['id','comment'])


if __name__ == '__main__':
    process = Data_precess()
    temp = process.read()
    process.data_to_csv(temp)
    pdb.set_trace()