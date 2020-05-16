# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html



class Text3ScrapydoubanPipeline(object):
    def __init__(self):
        self.file = open('dou.txt', 'w')

    def process_item(self, item, spider):
        a=str(dict(item))+"\n\n"
        self.file.write(a)
        return item

    def spider_closed(self,spider):
        self.file.close()
