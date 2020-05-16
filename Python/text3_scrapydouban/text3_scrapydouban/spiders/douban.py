# -*- coding: utf-8 -*-
import scrapy
from ..items import Text3Item


class DoubanSpider(scrapy.Spider):
    name = 'douban'
    count=0
    urls= 'https://book.douban.com/tag/小说?start='
    start_urls = [ urls + str(count)+ '&type=T']

    def parse(self, response):
        node_list=response.xpath("//div[@class='info']")#拿到最外层div
        for node in node_list:
            item=Text3Item()#itemd的类用来存储信息            
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
            a="分"
            item["grade"]=grade+a
            item["evaluate"]=evaluate
            yield item#引擎自动判断此为item数据，使用会自动交给管道
        if self.count<30 :
            self.count+=10
            url = self.urls+str(self.count)+'&type=T'
            yield scrapy.Request(url,callback=self.parse)#通过yield达到提交的效果，提交到引擎，引擎自动判断，此为request请求，然后调用相关函数

    
    

