# -*- coding: utf-8 -*-
import scrapy
from profession.items import ProfessionItem

class ScoreLineSpider(scrapy.Spider):
    name = 'Score_Line'
    #allowed_domains = ['ios.com']
    start_urls = ['http://college.koolearn.com/kaoyan/s/fs-0-0-0-0-57-20/?p=0']
    
    def parse(self, response):

        demo = response.xpath("//table/tr")        
        Demo = demo[2:]#去掉第一个表头，第一次的时候     
        for list in Demo:
            item=ProfessionItem()#创建一个item对象
            list_td=list.xpath("./td/text()").extract()
            list_td_a=list.xpath("./td/a/text()").extract()
            
            item["year"] = list_td[0]
            item["school_name"] = list_td_a[0]
            item["profession_name"] = list_td[1]
            item["marjon_code"] = list_td[2]
            item["marjon_name"] = list_td_a[1]
            item["sum_score"] = list_td[3]
            item["politics_score"] = list_td[4]
            item["English_score"] = list_td[5]
            item["three_score"] = list_td[6]
            item["four_score"] = list_td[7]
            yield item

        url="http://college.koolearn.com"+response.xpath("//a[text()='下一页']/@href").extract()[0]
        if url:
            yield scrapy.Request(url , callback=self.parse)

            
            


        

