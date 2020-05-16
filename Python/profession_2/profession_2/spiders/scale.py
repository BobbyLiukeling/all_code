# -*- coding: utf-8 -*-
import scrapy
from profession_2.items import Profession2Item_scale


class ScaleSpider(scrapy.Spider):
    name = 'scale'
    #allowed_domains = ['ios.com']
    start_urls = ['http://www.kaoshidian.com/kaoyan/bl-0-0-0-0-0.html?q=%E8%AE%A1%E7%AE%97%E6%9C%BA']

    def parse(self, response):
        demo=response.xpath("//table[@class='zhdetail']/tr")
        Demo=demo[2:]

        for list in Demo:
            item=Profession2Item_scale()
            list_td = list.xpath("./td/text()").extract()
            list_td_a = list.xpath("./td/a/text()").extract()

            item["year"] = list_td[0]
            item["area"] = list_td[1]
            item["school_name"] = list_td_a[0]
            item["profession_name"] = list_td[2]
            item["marjon_code"] = list_td[3]
            item["marjon_name"] = list_td_a[1]
            try:
                item["enroll_sum"] = list_td[4]
            except:
                item["enroll_sum"] = " "
            try:
                item["admit_sum"] = list_td[5]
            except:
                item["admit_sum"] =  " "
            try:
                item["scale_admit"] = list_td[6]
            except:
                item["scale_admit"] = " "
            try:
                item["excuse_sum"] = list_td[7]
            except:
                item["excuse_sum"] = " "
            yield item
