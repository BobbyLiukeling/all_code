# -*- coding: utf-8 -*-
import scrapy
import re

class StocksSpider(scrapy.Spider):
    name = 'stocks'
    #可选参数：allowed_dmains 这个参数是一个列表，里面可以有多个值
    start_urls = ['http://quote.eastmoney.com/stocklist.html']

    def parse(self, response):#由start_urls经过默认的request方法爬取下来的response对象
        headers = {
          'Accept-Encoding':'gzip, deflate, sdch, br',
          'Accept-Language':'zh-CN,zh;q=0.8',
          'Connection':'keep-alive',
          'Referer':'https://gupiao.baidu.com/',
          'User-Agent':'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
          }
        c=0
        for href in response.css("a::attr(href)").extract():#获取的是href的属性值
            if c>9:
                break
            else:
                try:
                    stock=re.findall(r"[s][zh]\d{6}",href)[0]#获取股票代码
                    url="https://gupiao.baidu.com/stock/" + "".join(stock) + ".html"#构建一个百度股票代码
                    yield scrapy.Request(url,callback=self.parse_stock,headers=headers)#产生生成器,Request将response修改为新生成的与百度相关的连接，callback参数指定产生的URL由后面的参数进行执行
                    c=c+1
                except:
                    continue
    def parse_stock(self,response):
        infoDict={}
        stockInfo=response.xpath("//div[@class='stock-bets']")#拿到最外层div
        stockInfo=response.css(".stock-bets")
        name=stockInfo.css(".bets-name").extract()[0]
        keyList=stockInfo.css("dt").extract()#获取文本内容
        valueList=stockInfo.css("dd").extract()
        for i in range(len(keyList)):
            key=re.findall(r">.*</dt>",keyList[i])[0][1:-5]
            try:
                val=re.findall(r"\d\.?.*<\dd>",valueList[i])[0][0:-5]
            except:
                val="--"
            infoDict[key]=val

        infoDict.update({'股票名称': re.findall('\s.*\(',name)[0].split()[0] +re.findall('\>.*\<', name)[0][1:-1]})
        yield infoDict
