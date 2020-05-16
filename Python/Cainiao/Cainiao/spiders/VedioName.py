# -*- coding: utf-8 -*-
import scrapy
from ..items import CainiaoItem
import time
import re


class VedionameSpider(scrapy.Spider,):
    name = 'VedioName'
    #allowed_domains = ['cainiao.com']
    start_urls = ['http://www.newbiefly.com/?post_type=gift']


    def parse(self, response):
        list_href = response.xpath("//div[@class='panel-body gift_filter']/dl/dd/ul/li")
        for list in list_href:
            type = list.xpath(".//a/text()").extract()[0].strip()
            type_href = list.xpath(".//a/@href").extract()[0]
            count = re.match(".*(&t=\d+)", type_href).group(1)#链接的后缀  &t=17
            yield scrapy.Request(url=type_href, meta={"type":type, "count":count}, callback=self.parse_list)
            time.sleep(0.1)


    def parse_list(self, response):
        lists = response.xpath("//div[@class='row clearfix']/article")
        for list in lists:
            type = response.meta.get("type","") #类型
            try:
                title = list.xpath(".//div[@class='entry-meta']/a/text()").extract()[0].strip()
            except:
                title = "没有标题"
            content_href =list.xpath(".//div[@class='entry-meta']/a/@href").extract()[0]
            try:
                score = list.xpath(".//div[@class='entry-meta']/span/text()").extract()[0]
            except:
                score = list.xpath(".//div[@class='entry-meta']/span/em/text()").extract()[0]
            #img_href = list.xpath(".//img/@src").extract()[0]
            item = CainiaoItem()
            item["type"] = type
            item["title"] = title
            item["href"] = content_href
            item["score"] = score
            #item["img_href"] = img_href
            yield item
        time.sleep(0.1)#爬取速度太快会返回429

        try:
            next_page_href = response.xpath("//a[@class='next page-numbers']/@href").extract()[0]
            yield scrapy.Request(url=next_page_href, callback=self.parse_list)
        except:
            pass