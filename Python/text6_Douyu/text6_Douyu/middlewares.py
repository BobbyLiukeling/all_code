# -*- coding: utf-8 -*-

# Define here the models for your spider middleware
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/spider-middleware.html

from scrapy import signals
import time
from selenium import webdriver
from scrapy.http.response.html import HtmlResponse
from scrapy.http.response import Response

class Text6DouyuSpiderMiddleware(object):
    # Not all methods need to be defined. If a method is not defined,
    # scrapy acts as if the spider middleware does not modify the
    # passed objects.
    
 
    @classmethod
    def from_crawler(cls, crawler):
        # This method is used by Scrapy to create your spiders.
        s = cls()
        crawler.signals.connect(s.spider_opened, signal=signals.spider_opened)
        return s

    def process_spider_input(self, response, spider):
        # Called for each response that goes through the spider
        # middleware and into the spider.
        # Should return None or raise an exception.
        return None

    def process_spider_output(self, response, result, spider):
        # Called with the results returned from the Spider, after
        # it has processed the response.

        # Must return an iterable of Request, dict or Item objects.
        for i in result:
            yield i

    def process_spider_exception(self, response, exception, spider):
        # Called when a spider or process_spider_input() method
        # (from other spider middleware) raises an exception.

        # Should return either None or an iterable of Response, dict
        # or Item objects.
        pass

    def process_start_requests(self, start_requests, spider):
        # Called with the start requests of the spider, and works
        # similarly to the process_spider_output() method, except
        # that it doesn’t have a response associated.

        # Must return only requests (not items).
        for r in start_requests:
            yield r

    def spider_opened(self, spider):
        spider.logger.info('Spider opened: %s' % spider.name)


# class Text6DouyuDownloaderMiddleware(object):
#     # Not all methods need to be defined. If a method is not defined,
#     # scrapy acts as if the downloader middleware does not modify the
#     # passed objects.
#     super(Text6DouyuSpiderMiddleware, self).__init__()
#     RequestDownloadMiddleWare(object):
#     self.driver = webdriver.Chrome()
#     def process_request(self,request,spider):
#
#         if spider.name= 'Douyu_info':
#             spider.driver.get(request.url)
#             print("深V股v结婚两个关于一一一一一一一一一")
#             print(request.url)
#             '''for x in xrange(1,11,2):
#                 i=float(x)/10
#                 js="document.body.scrollTop=document.body.scrollHeight * %f"%i
#                 spider.driver.execute_script(js)
#                 time.sleep(1)'''
#             response = Response(url = request.url,body=bytes(spider.driver.page_source),request = request)
#         return response
    
