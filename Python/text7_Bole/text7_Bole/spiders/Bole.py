# -*- coding: utf-8 -*-
import scrapy


class BoleSpider(scrapy.Spider):
    name = 'Bole'
    allowed_domains = ['blog.jobbole.com']
    start_urls = ['http://blog.jobbole.com/']

    def parse(self, response):
        pass
