# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html


class BaiduscrapyPipeline(object):
    def process_item(self, item, spider):
        return item


class BaidustockInfoPipline(object):
    def open_spider(self,spider):#启动自动调用爬虫时的方法
        self.f=open("BaiduStockInfo.txt","wb")

    def close_spider(self,spider):#关闭时自动调用
        self.f.close()

    def process_item(self,item,spider):#对每一个item处理时调用
        try:
            line=str(dict(item))+"\n"
            self.f.write(line)
        except:
            pass
        return item