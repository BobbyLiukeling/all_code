# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class Text6DouyuItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()

    nickname=scrapy.Field()
    image_href=scrapy.Field()
