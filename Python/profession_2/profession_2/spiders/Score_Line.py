# -*- coding: utf-8 -*-
import scrapy
from profession_2.items import Profession2Item

class ScoreLineSpider(scrapy.Spider):
    name = 'Score_Line'
    #allowed_domains = ['ios.com']
    start_urls = ['http://www.kaoshidian.com/kaoyan/fs-0-0-0-0-0.html?q=计算机']

    def parse(self, response):
        demo = response.xpath("//table[@class='zhdetail']/tr")        
        demo = demo[2:]#去掉表头
        for list in demo:
            item = Profession2Item()
            list_td = list.xpath("./td/text()").extract()
            list_td_a = list.xpath("./td/a/text()").extract()
         
            item["year"] = list_td[0]
            item["school_name"] = list_td_a[0]
            item["profession_name"] = list_td[1]
            item["marjon_code"] = list_td[2]
            item["marjon_name"] = list_td_a[1]
            try:
                item["sum_score"] = list_td[3]
            except:
                item["sum_score"] = " "
            try:
                item["politics_score"] = list_td[4]
            except:
                item["politics_score"] =  " "
            try:
                item["English_score"] = list_td[5]
            except:
                item["English_score"] = " "
            try:
                item["three_score"] = list_td[6]
            except:
                item["three_score"] = " "
            try:        
                item["four_score"] = list_td[7]
            except:
                item["four_score"] = " "
            yield item
        
        try:
            url=response.xpath("//a[text()='下一页']/@href").extract()[0]
            print(url)
            if url:
                yield response.follow(url , callback=self.parse)#scrapy.Request=response.follow
        except:#解析到最后一个会有问题，下面的程序不能执行
            pass


        
