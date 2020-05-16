# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
import xlsxwriter
import requests
from bs4 import BeautifulSoup

class Profession2Pipeline_line(object):
    def __init__(self):
        self.workbook=xlsxwriter.Workbook("Score_Line.xlsx")
        self.worksheet=self.workbook.add_worksheet()
        self.cols=1
        html_line=requests.get('http://www.kaoshidian.com/kaoyan/fs-0-0-0-0-0.html?q=计算机')
        
        soup=BeautifulSoup(html_line.text,"html.parser")
        head=soup.find_all("table",{"class":"zhdetail"})[0].find_all("td")
        k=0
        for i in head:#写入头
            self.worksheet.write(0,k,i.string) 
            k+=1

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
    
    def process_closed(self):
        self.worksheet.close()

class Profession2Pipeline_scale(object):
    def __init__(self):
        self.workbook=xlsxwriter.Workbook("Score_Scale.xlsx")
        self.worksheet=self.workbook.add_worksheet()
        self.cols=1
        html_scale=requests.get('http://www.kaoshidian.com/kaoyan/bl-0-0-0-0-0.html?q=%E8%AE%A1%E7%AE%97%E6%9C%BA')
        
        soup=BeautifulSoup(html_scale.text,"html.parser")
        head=soup.find_all("table",{"class":"zhdetail"})[0].find_all("td")
        k=0
        for i in head:#写入头
            self.worksheet.write(0,k,i.string) 
            k+=1

    def process_item(self, item, spider):
        try:   
            self.worksheet.write(self.cols,0,item["year"])
            self.worksheet.write(self.cols,1,item["area"])
            self.worksheet.write(self.cols,2,item["school_name"])
            self.worksheet.write(self.cols,3,item["profession_name"])
            self.worksheet.write(self.cols,4,item["marjon_code"])
            self.worksheet.write(self.cols,5,item["marjon_name"])
            self.worksheet.write(self.cols,6,item["enroll_sum"])
            self.worksheet.write(self.cols,7,item["admit_sum"])
            self.worksheet.write(self.cols,8,item["scale_admit"])
            self.worksheet.write(self.cols,9,item["excuse_sum"])
            self.cols+=1
        except:
            print("写入失败")
        return item
    
    def process_closed(self):
        self.worksheet.close()

