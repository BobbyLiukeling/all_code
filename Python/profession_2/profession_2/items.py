# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class Profession2Item(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    #年份	学校名称	院系名称	专业代码	专业名称	总分	政治/科目一	外语/科目二	科目三	科目四
    year=scrapy.Field()
    school_name=scrapy.Field()
    profession_name=scrapy.Field()
    marjon_code=scrapy.Field()
    marjon_name=scrapy.Field()
    sum_score=scrapy.Field()
    politics_score=scrapy.Field()
    English_score=scrapy.Field()
    three_score=scrapy.Field()
    four_score=scrapy.Field()

class Profession2Item_scale(scrapy.Item):

    #年份	地区	学校	学院	专业代码	专业名称	报名人数	录取人数	报录比	推免人数
    year=scrapy.Field()
    area=scrapy.Field()
    school_name=scrapy.Field()
    profession_name=scrapy.Field()
    marjon_code=scrapy.Field()
    marjon_name=scrapy.Field()
    enroll_sum=scrapy.Field()#报名人数
    admit_sum=scrapy.Field()
    scale_admit=scrapy.Field()
    excuse_sum=scrapy.Field()#免试人数
    
