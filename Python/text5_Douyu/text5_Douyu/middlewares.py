# -*- coding: utf-8 -*-

# Define here the models for your spider middleware
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/spider-middleware.html
import time
from selenium import webdriver
from scrapy.http.response.html import HtmlResponse

from scrapy import signals
import pdb


class Text5DouyuSpiderMiddleware(object):
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

import pdb
class Text5DouyuDownloaderMiddleware(object):
    # Not all methods need to be defined. If a method is not defined,
    # scrapy acts as if the downloader middleware does not modify the
    # passed objects.
    


    # @classmethod
    # def from_crawler(cls, crawler):
    #     # This method is used by Scrapy to create your spiders.
    #     s = cls()
    #     crawler.signals.connect(s.spider_opened, signal=signals.spider_opened)
    #     return s
    #
    # def process_request(self, request, spider):
    #     # Called for each request that goes through the downloader
    #     # middleware
    #     return None
    #

    def process_response(self, request, response, spider):
        web = webdriver.Chrome("E:/software/python3.6/chromedriver.exe")
        url = 'https://search.jd.com/Search?keyword=iphone8%E6%89%8B%E6%9C%BA&enc=utf-8&spm=a.0.0&pvid=391abe80e182462ca5559693e6b4d37e'
        try:
            if spider.name == "DouyuImage":
                # self.web.get(request.url)
                web.get(url)
                time.sleep(3)
                # pdb.set_trace()
                body = web.page_source
                print("访问:{0}".format(url))
                print("^" * 50)
                return HtmlResponse(url=web.current_url, body=body, encoding="utf-8", request=request)
                # return response
        except Exception as e:
            print(e)
            print("webdriver 失败")
            return response
    #
    # def process_exception(self, request, exception, spider):
    #     # Called when a download handler or a process_request()
    #     # (from other downloader middleware) raises an exception.
    #
    #     # Must either:
    #     # - return None: continue processing this exception
    #     # - return a Response object: stops process_exception() chain
    #     # - return a Request object: stops process_exception() chain
    #     pass

class JSMiddleware(object):
    def process_request(self, request, spider):
        web = webdriver.Chrome("E:/software/python3.6/chromedriver.exe")
        try:
            if spider.name == "DouyuImage":
                # self.web.get(request.url)
                web.get(request.url)
                time.sleep(3)
                body = web.page_source
                print("访问:{0}".format(request.url))
                print("^" * 50)
                return HtmlResponse(url=web.current_url, body=body, encoding="utf-8", request=request)
        except Exception as e:
            print(e)
            print("webdriver 失败")
            return None

