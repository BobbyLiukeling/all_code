# -*- coding: utf-8 -*-
import scrapy
from  ..items import Text2Item


class DoubanSpider(scrapy.Spider):
    name = 'douban'
    count = 0
    start_urls = ['https://book.douban.com/tag/小说?start='+str(count)+'&type=T']
    
    
    
    def parse(self, response):        
        items=[]
        node_list=response.xpath("//div[@class='info']")#拿到最外层div
        for node in node_list:
            item = DoubanSpider()#itemd的类用来存储信息
            #extract将Xpath对象转换为Unicode方便解读
            bookname=node.xpath("./h2/a/text()").extract()[0].strip()#rstrip()将右边的空格去掉
            title=node.xpath("./div[1]/text()").extract()[0].split("/")
            author=title[0].strip()
            publishTime=title[-2]
            bookprice=title[-1].strip()
            grade=node.xpath("./div[2]/span[2]/text()").extract()[0]#等级
            evaluate=node.xpath("./p/text()").extract()[0]


            item['bookname']=bookname
            item["author"]=author
            item["time"]=publishTime
            item["price"]=bookprice
            item["grade"]=grade+"分"
            item["evaluate"]=evaluate 
            print(item["bookname"])
            items.append(item)            
        return items
    
    
