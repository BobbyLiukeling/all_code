# -*- coding: utf-8 -*-
import scrapy
from selenium import webdriver
# from text6_Douyu.items import Text6DouyuItem

class DouyuInfoSpider(scrapy.Spider):
    name = 'Douyu_Info'
    #allowed_domains = ['douyu.com']
    start_urls = ['https://yuba.douyu.com/allclassify/anchorlist/list/516']

    def __init__(self):
        pass


    def parse(self, response):
        print(response.text)
        
    #     item=Text6DouyuItem()
    #     super(DouyuInfoSpider,self).__init__()
    #     self.driver=webdriver.Chrome()
    #     list_item=response.xpath("//div[@class='classify-classifyGroup-1lMJV']/div")
    #     print(type(response))
    #     if response:
    #         pass
    #         #print("response.xpath("//div[@class='classify-classifyGroup-1lMJV']/div")")
    #     #list_item=soup.find_all("div",class_="classify-classifyGroup-1lMJV")#主页所有主播链接
    #     for list in list_item:
    #         nickname=list.xpath("//div[0]/p/text()").extract()[0]
    #         #nickname=list.find("div",class_="style-itemTex-EZ_Wl").p.text#主播姓名
    #         #image_href=list.find("img")["@src"]#获取img标签下的src链接
    #         image_href=list.xpath("//image/@src").extract()[0]
    #
    #         item[nickname]=nickname
    #         item[image_href]=image_href
    #         yield item
    #
    # def closed(self,reason):
    #     print("爬虫关闭原因：",reason)
    #     #self.driver.quit()
