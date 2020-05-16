# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
import scrapy
from scrapy.pipelines.images import ImagesPipeline
import os
import json
from .settings import IMAGES_STORE as image_store
import codecs
import MySQLdb.cursors
from twisted.enterprise import adbapi
import MySQLdb
#from scrapy.exporters import JsonItemExporter



class ArticalsoiderPipeline(object):#自定义将文件保存为json文件
    def __init__(self):
        self.file = codecs.open("bole.json", "wb", encoding="utf-8")

    def process_item(self, item, spider):
        item["create_time"] = str(item["create_time"])#当保存时，json文件会和create_time的date类型冲突
        lines = json.dumps(dict(item), ensure_ascii=False) + "\n" #保证正常的中文编码
        self.file.write(lines)
        return item

    def closed(self):
        self.file.close()


# class JsonExporterPipelines(object):
#     #调用scrapy提供 的jsonexporter导出json文件
#     def __init__(self):
#         self.file = open("articalJson.json", "wb")
#         self.exporter = JsonItemExporter(self.file, encoding="utf-8",ensure_ascii=False)
#         self.exporter.start_exporting()
#
#     def closer_spider(self, spider):
#         self.exporter.finish_exporting()
#         self.file.close()
#
#     def process_item(self, itme, spider):
#         self.exporter.export_item(item)
#         return item


class ArticalImagePipeline(ImagesPipeline):
    def get_media_requests(self, item, info):#图片下载
        image_link = item["front_image_url"]
        yield scrapy.Request(image_link)

    def item_completed(self, results, item, info):#修改图片保存路径，及获得路径
        value = [x["path"] for ok, x in results if ok]
        try:
            os.rename(image_store + "\\"+value[0], image_store + "\\"+item["title"] + ".jpg")#中间记得要加斜杠
            item["front_image_path"] = image_store + "\\"+item["title"] + ".jpg"
            a = item["front_image_path"]
        except:
            pass
        return item


# class MysqlPipelines(object): #当数据量比较少是可以用这个代码进行mysql的存储，插入的同步操作
#     def __init__(self):
#         self.conn = MySQLdb.Connect(host = "127.0.0.1",
#                                     port = 3306,
#                                     user = "root",
#                                     passwd = "520lkl",
#                                     db = "pytohn",
#                                     charset = "utf8",
#                                     use_unicode=True)
#         self.cursor = self.conn.cursor()
#
#     def process_item(self, item, spider):
#         insert_sql = "insert into bole(title, url_object_id, create_date, fav_nums) values(%s, %s, %s, %s)"
#         print(self.cursor)
#         print(self.conn)
#         self.cursor.execute(insert_sql, (item["title"], item["url_hashcode"], item["create_time"], item["praise_number"]))
#         self.conn.commit()
#
#     def closed(self):
#         self.cursor.close()
#         self.conn.close()


class MysqlTwistedPipelines(object):#插入的异步操作
    def __init__(self, dbpool):
        self.dbpool =dbpool

    @classmethod
    def from_settings(cls, settings):
        daparms = dict(
            host = settings["MYSQL_HOST"],
            db = settings["MYSQL_DBNAME"],
            user = settings["MYSQL_USER"],
            password = settings["MYSQL_PASSWORD"],
            charset = "utf8",
            cursorclass = MySQLdb.cursors.DictCursor,
            use_unicode = True
        )
        dbpool = adbapi.ConnectionPool("MySQLdb", **daparms)
        return cls(dbpool)

    def process_item(self, item, spider):
        query = self.dbpool.runInteraction(self.do_insert, item)
        query.addErrback(self.handle_error, item, spider)#处理异常

    def handle_error(self, failure, item, spider):
        #处理异步插入的异常
        print(failure)

    def do_insert(self, cursor, item):
        #执行具体的插入
        insert_sql = "insert into bole(title, url_object_id, create_date, fav_nums) values(%s, %s, %s, %s)"
        cursor.execute(insert_sql, (item["title"], item["url_hashcode"], item["create_time"], item["praise_number"]))

        pass
