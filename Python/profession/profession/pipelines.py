# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
import xlsxwriter

class ProfessionPipeline(object):
    def __init__(self):
        self.workbook=xlsxwriter.Workbook("demo.xlsx")#创建一个工作表,注意Workbook的大小写
        self.worksheet=self.workbook.add_worksheet()#创建一个工作表对象
        self.cols=1#横
        #写入表头
        self.worksheet.write(0,0,"年份")
        self.worksheet.write(0,1,"学校名称")
        self.worksheet.write(0,2,"院系名称")
        self.worksheet.write(0,3,"专业代码")
        self.worksheet.write(0,4,"专业名称")
        self.worksheet.write(0,5,"总分")
        self.worksheet.write(0,6,"政治")
        self.worksheet.write(0,7,"英语")
        self.worksheet.write(0,8,"第三专业")
        self.worksheet.write(0,9,"第四专业")                                                                                                                                                                                                                        ")
        


    def process_item(self, item, spider):
        try:    
            self.worksheet.write(self.cols,0,item["year"])
            self.worksheet.write(self.cols,1,item["school_name"])
            self.worksheet.write(self.cols,2,item["profession_name"])
            self.worksheet.write(self.cols,3,item["marjon_code"])
            self.worksheet.write(self.cols,4,item["marjon_name"])
            self.worksheet.write(self.cols,5,item["sum_score"])
            self.worksheet.write(self.cols,6,item["politics_score"])
            self.worksheet.write(self.cols,7,item["English_score"])
            self.worksheet.write(self.cols,8,item["three_score"])
            self.worksheet.write(self.cols,9,item["four_score"])
            self.cols+=1
        except:
            print("写入失败")
        return item

    def spider_closed(self):
        self.worksheet.close()
