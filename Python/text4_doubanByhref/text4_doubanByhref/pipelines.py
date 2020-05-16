# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
#当在线解析json格式文件时，需要手动在源码前后加上中括号，并且去掉最后面的逗号
import json
class Text4DoubanbyhrefPipeline(object):
    def __init__(self):
        self.file = open('dou.json', 'w')

    def process_item(self, item, spider):
        a=json.dumps(dict(item))+",\n\n"
        self.file.write(a)
        return item

    def spider_closed(self,spider):
        self.file.close()
