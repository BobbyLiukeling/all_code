# -*- coding: utf-8 -*-

class DemoSpider(scrapy.Spider):
    name = 'demo'
    #allowed_domains = ['www.baidu.com']
    start_urls = ['http://www.baidu.com/']

    def parse(self, response):
        a=response.xpath("//div[@id='head']")
        print(a)
