# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class Text2Item(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    bookname=scrapy.Field()
    author=scrapy.Field()
    time=scrapy.Field()
    price=scrapy.Field()
    grade=scrapy.Field()#豆瓣口碑
    evaluate=scrapy.Field()#简述
