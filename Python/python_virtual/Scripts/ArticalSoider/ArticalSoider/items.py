# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy
from scrapy.loader.processors import MapCompose, TakeFirst, Join
from scrapy.loader import ItemLoader #拿到takefirst
import re
import datetime

# class ArticalsoiderItem(scrapy.Item):
#     # define the fields for your item here like:
#     # name = scrapy.Field()
#     title = scrapy.Field()
#     create_time = scrapy.Field()
#     front_image_url = scrapy.Field()
#     front_image_path = scrapy.Field()
#     praise_number = scrapy.Field()
#     colloct_number = scrapy.Field()
#     conmment_number = scrapy.Field()
#     content = scrapy.Field()
#     tag = scrapy.Field()
#     url_hashcode = scrapy.Field() #得到URL生成的哈希码


class Item_Takefirst(ItemLoader):#自定义拿到takefirst
    default_output_processor = TakeFirst()


def time_convert(value):
    #value = (re.match(".*(\d+)/(\d+)/(\d+).*?", value).group(1))
    value = value.replace("\r", "").replace("\n", "").replace("·", "").strip()
    try:
        value = datetime.datetime.strptime(value, "%Y/%m/%d").date()
    except Exception as e:
        value = datetime.datetime.now().date()
        #print(e)
    return value


def praise_convert(value):
    try:
        value = int(value)
    except:
        value = 0
    return value


def colloct_convert(value):
    try:
        value = int(re.match(".*(\d+).*?", value).group(1))
    except:
        value = 0
    return value


def comment_convert(value):
    try:
        value = (re.match(".*(\d+).*?", value).group(1))
    except:
        value = 0
    return value


def tag_convert(value):
    try:
        value = [element for element in value if not element.strip().endswith("评论")]  # 去掉评论这个标签 输出结果['职场', ' 7 评论 ', '程序员', '职场']
        # value = dict.fromkeys(value,1)
        # value = list(value.keys())
        # value = ",".join(value)
    except:
        value = "没有标签"
    return value


def return_value(value):#去掉takefirst效果
    return value


class ArticalsoiderItem(scrapy.Item):#重置item用于配置item_loder
    # define the fields for your item here like:
    # name = scrapy.Field()
    title = scrapy.Field()  #output_processor = TakeFirst()
    create_time = scrapy.Field(
        input_processor=MapCompose(time_convert)
    )
    front_image_url = scrapy.Field(
        out_processor=MapCompose(return_value)#image_url需要是一个list，所以要去掉str属性
    )
    front_image_path = scrapy.Field()
    praise_number = scrapy.Field(
        input_processor=MapCompose(praise_convert)
    )
    colloct_number = scrapy.Field(
        input_processor=MapCompose(colloct_convert)
    )
    conmment_number = scrapy.Field(
        input_processor=MapCompose(comment_convert)
    )
    content = scrapy.Field()
    tag = scrapy.Field(
        out_processor=MapCompose(tag_convert)#和前面的不一样，因为tag本身就是一个list所以在经过takefirst进行str以后就会出问题，所以现在要对tag进行还原成list，即重写out_processor
    )
    url_hashcode = scrapy.Field() #得到URL生成的哈希码