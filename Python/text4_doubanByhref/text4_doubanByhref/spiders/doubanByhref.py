# -*- coding: utf-8 -*-
#author:bobby
#关键词：scrapy
#从豆瓣中提取小说的相关内容，下一页从网页中自动提取
#直接从网页链接中提取下一页
import scrapy
from text4_doubanByhref.items import Text4DoubanbyhrefItem

class DoubanbyhrefSpider(scrapy.Spider):
    name = 'doubanByhref'
    #allowed_domains = ['https://book.tuicool.com']
    count=0
    urls= 'https://book.douban.com/tag/小说?start='
    start_urls = [ urls + str(count)+ '&type=T']
    
    
    
    def parse(self, response):
        
        node_list=response.xpath("//div[@class='info']")#拿到最外层divscrapy crawl doubanByhref
        a=response.xpath("//p[@class='pl2']")#当前页如果存在此标签则当前页没有信息
        if a:#如果找到最后一页的下一页退出
                print("最后一页")
        else:            
            for node in node_list:            
                item=Text4DoubanbyhrefItem()#itemd的类用来存储信息            
                #extract将Xpath对象转换为list对象方便解读
            
                bookname=node.xpath("./h2/a/text()").extract()[0].strip()#rstrip()将右边的空格去掉
                title=node.xpath("./div[1]/text()").extract()[0].split("/")
                author=title[0].strip()
                publishTime=title[-2]
                bookprice=title[-1].strip()
                
                

                item['bookname']=bookname
                item["author"]=author
                item["time"]=publishTime
                item["price"]=bookprice
                try:#评分可能为空
                    grade=node.xpath("./div[2]/span[2]/text()").extract()[0]#等级
                    a="分"
                    item["grade"]=grade+a
                except:
                    item["grade"]="评价太少，没有评分"
                try:#评价可能为空
                    evaluate=node.xpath("./p/text()").extract()[0]
                    item["evaluate"]=evaluate
                except:
                    item["evaluate"]="没有评论"
#yield在返回数据后还能继续执行
                yield item#引擎自动判断此为item数据，使用会自动交给管道，还要记得在seting里面激活管道

           #没有找到最后一页下一页                   
            url="https://book.douban.com"+response.xpath("//span[@class='next']/a/@href").extract()[0]
            yield scrapy.Request(url,callback=self.parse)#通过yield达到提交的效果，提交到引擎，引擎自动判断，此为request请求，然后调用相关函数
