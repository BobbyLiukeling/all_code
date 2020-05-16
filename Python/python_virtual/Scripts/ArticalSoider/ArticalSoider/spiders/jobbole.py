# -*- coding: utf-8 -*-
import scrapy
import re
from ..items import ArticalsoiderItem, Item_Takefirst
from ..self_page.common import get_md5
from urllib import parse
import datetime
from scrapy.loader import ItemLoader


class JobboleSpider(scrapy.Spider):
    name = 'jobbole'
    # allowed_domains = ['bole.job.com']
    start_urls = ['http://blog.jobbole.com/category/career/']

    def parse(self, response):
        # 1、获取所有页面链接，并交给解析函数
        # 2、获取下一页并交给scrapy下载，并交给parser函数
        href_nodes = response.xpath("//div[@class='post floated-thumb']")
        for node in href_nodes:
            image_href = node.xpath(".//img/@src").extract()[0]
            image_href = parse.urljoin(response.url,image_href)#防止域名不全
            content_href = node.xpath(".//div[@class='post-thumb']/a/@href").extract()[0]
            content_href = parse.urljoin(response.url,content_href)
            yield scrapy.Request(content_href, meta={"front_image_url": image_href},callback=self.parse_detail)  # parse_detail后面不加括号？？？？ 不知道为什么

        # try:
        #     next_page_href = response.xpath("//a[@class='next page-numbers']/@href").extract()[0]  # 下一页链接
        #     yield scrapy.Request(next_page_href, callback=self.parse)
        # except:
        #     print("最后一页下载完成")
        # print()

    # def parse_detail(self, response):#  普通item解析网页版本
    #     item = ArticalsoiderItem()
    #     # 解析具体的response
    #     title = response.xpath("//div[@class='entry-header']/h1/text()").extract()[0]
    #     # 时间中包括点号和空字符串
    #     create_time = response.xpath("//p[@class='entry-meta-hide-on-mobile']/text()").extract()[0].replace("·","").strip()
    #     front_image_url=response.meta.get("front_image_url","")   #封面图链接
    #     try:
    #         praise_number = int(response.xpath(
    #             "//span[@class=' btn-bluet-bigger href-style vote-post-up   register-user-only ']/h10/text()").extract()[0])
    #     except:
    #         praise_number = 0
    #     try:
    #         colloct_number = int((re.match(".*(\d+).*?", response.xpath("//span[@class=' btn-bluet-bigger href-style bookmark-btn  register-user-only ']/text()").extract()[0])).group(1))  # 收藏
    #     except:
    #         colloct_number = 0
    #     try:
    #         conmment_number = int((re.match(".*(\d+).*?", response.xpath("//span[@class='btn-bluet-bigger href-style hide-on-480']/text()").extract()[0])).group(1))  # 评论
    #     except:
    #         conmment_number = 0
    #     content = response.xpath("//div[@class='entry']/p").extract()  # 正文
    #
    #     tag = response.xpath("//div[@class='entry-meta']/p/a/text()").extract()
    #     tag = [element for element in tag if not element.strip().endswith("评论")]  # 去掉评论这个标签 输出结果['职场', ' 7 评论 ', '程序员', '职场']
    #     tag = dict.fromkeys(tag, 1)  # 输出结果 {'职场': 1, '程序员': 1}
    #     tag = list(tag.keys())  # 输出结果 ['职场', '程序员']
    #     tag = ",".join(tag)
    #
    #     #将数据存入item
    #     item["title"] = title
    #     try:
    #         create_time = datetime.datetime.strptime(create_time, "%Y/%m/%d").date()
    #     except:
    #         create_time = datetime.datetime.now().date()
    #     item["create_time"] = create_time
    #     item["front_image_url"] = front_image_url
    #     item["praise_number"] = praise_number
    #     item["colloct_number"] = colloct_number
    #     item["conmment_number"] = conmment_number
    #     item["content"] = content
    #     item["tag"] = tag
    #     item["url_hashcode"] = get_md5(response.url)
    #     yield item

    def parse_detail(self, response):#通过itemloder加载item
        #全部都只提取基本的xpath 但是具体的对最后xpath的结果的解析在item中完成
        #item_loder = ItemLoader(item = ArticalsoiderItem(), response = response)#得到的item是list类型
        item_loder = Item_Takefirst(item=ArticalsoiderItem(), response=response)  # 得到的item是str类型
        #item_loder.add_css()
        item_loder.add_xpath("title", "//div[@class='entry-header']/h1/text()")
        item_loder.add_xpath("create_time", "//p[@class='entry-meta-hide-on-mobile']/text()")
        item_loder.add_value("front_image_url", response.meta.get("front_image_url",""))
        item_loder.add_xpath("praise_number", "//span[@class=' btn-bluet-bigger href-style vote-post-up   register-user-only ']/h10/text()")
        item_loder.add_xpath("colloct_number", "//span[@class=' btn-bluet-bigger href-style bookmark-btn  register-user-only ']/text()")
        item_loder.add_xpath("conmment_number", "//span[@class='btn-bluet-bigger href-style hide-on-480']/text()")
        item_loder.add_xpath("content", "//div[@class='entry']/p")
        item_loder.add_xpath("tag", "//div[@class='entry-meta']/p/a/text()")
        item_loder.add_value("url_hashcode", get_md5(response.url))


        item = item_loder.load_item()#现在item的数据都是list类型
        print("召开就行了了开发了吧就看书")
        b=item["title"]
        print(b)
        a=item["create_time"]
        print(a)
        print(type(a))
        yield item