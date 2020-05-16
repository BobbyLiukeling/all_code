# -*- encoding: utf-8 -*-
# @author : bobby
# @time : 2020/2/16 21:17
'''
从数据库中将豆瓣评论取出
分数为5星的为积极评论，为一星和两星的为消极评论
将积极和消极评论分别存入txt文本中以待训练模型使用
'''

from snownlp import sentiment
import pdb
import pymysql
import re

# sentiment.train('neg.txt', 'pos.txt')
# sentiment.save('sentiment.marshal')

class handle:

    def __init__(self):
        self.db = pymysql.connect(host="localhost", port=3306, user="root", passwd='867425', db="sentiment_train",charset="utf8mb4")
        # 使用 cursor() 方法创建一个游标对象 cursor
        self.cursor = self.db.cursor()

    @staticmethod
    def close(self):
        self.cursor.close()


    def read_sql(self): # weibo_essay
        '''
        将comment数据从数据库中读出
        :return:
        '''
        sql ="select comment from douban where rating=1 or rating = 2"
        # sql = 'select content from weibo_essay where id<500 '
        self.cursor.execute(sql)
        temp = self.cursor.fetchall()# 获取结果集列表
        # pdb.set_trace()
        return temp



    def text_save(self,filename, data = []  ):#filename为写入CSV文件的路径，data为要写入数据列表.
        temp = []
        # pdb.set_trace()
        for i in data:
            i = self.textParse(i[0])
            if i !='':
                temp.append(i)
        data = temp
        files = open(filename,'a+',encoding='utf-8')
        files.writelines(data)
        files.close()

    def textParse(self,str_doc):
        # 正则过滤掉特殊符号、标点、英文、数字等。
        r1 = '[a-zA-Z’"#$%&\'()*+-/:|<=>，—★【】[\\]^_`{|}~]+'
        str_doc = re.sub(r1, ' ', str_doc)
        return str_doc


if __name__ == '__main__':
    temp = handle()
    data = temp.read_sql()
    filename = 'neg.txt'
    temp.text_save(filename,data)
