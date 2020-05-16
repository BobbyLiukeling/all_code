# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html


class Text6DouyuPipeline(object):
    def process_item(self, item, spider):
        def __init__(self):
            self.f=open("douyu.txt","wb")

        def process_item(self,item,spider):
            self.f.write(item)
            return item
            
        def spider_closed(self):
            self.f.close()
    
