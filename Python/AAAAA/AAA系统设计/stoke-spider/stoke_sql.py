# -*- coding: UTF-8 -*-
import requests
from bs4 import BeautifulSoup as bf
import pymysql
from spider import *
#爬取网站
#存入sql数据库
def save_sql(num,year):
    #连接数据库
    db=pymysql.connect(host='localhost',user='root',password='mizunoakira',port=3306,db='spiders')
    cursor=db.cursor()
    #建表
    name=get_name(num)
    cursor.execute("DROP TABLE IF EXISTS "+name)
    sql = "CREATE TABLE "+name+""" (
        date_val CHAR(20),
        p_start FLOAT(10),
        p_high FLOAT(10),
        p_low FLOAT(10),
        p_fin FLOAT(10),
        ch_val FLOAT(10),
        ch_per FLOAT(10))"""
    cursor.execute(sql)
    for season in range(1,4):
        url='http://quotes.money.163.com/trade/lsjysj_'+str(num)+'.html?year='+str(year)+'&season='+str(season)
        html=request_stoke(url)
        soup=bf(html,'lxml')
        trs=soup.find(class_='table_bg001 border_box limit_sale').find_all('tr')
        for tr in trs:
            tds=tr.find_all('td')
            td=[x for x in tds]
            if len(td)>=1 and td[0]!='':
                date_val=td[0].text.strip()
                p_start=float(td[1].text)
                p_high=float(td[2].text)
                p_low=float(td[3].text)
                p_fin=float(td[4].text)
                ch_val=float(td[5].text)
                ch_per=float(td[6].text)
                #change=td[9].text.strip()
                #intern=td[10].text.strip()
                insert_stoke =("INSERT INTO "+name+"(date_val,p_start,p_high,p_low,p_fin,ch_val,ch_per)"+"VALUES(%s,%f,%f,%f,%f,%f,%f)")
                data_stoke = (date_val,p_start,p_high,p_low,p_fin,ch_val,ch_per)
                cursor.execute(insert_stoke%data_stoke)
                db.commit()
        print("Finish")
if __name__ == '__main__':
    save_sql(601318,2018
)
