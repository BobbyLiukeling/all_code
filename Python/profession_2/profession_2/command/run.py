from scrapy.commands import ScrapyCommand  
from scrapy.crawler import CrawlerRunner
from scrapy.utils.conf import arglist_to_dict

class Command(ScrapyCommand):
  
    requires_project = True
  
    def syntax(self):  
        return '[options]'  
  
    def short_desc(self):  
        return 'Runs all of the spiders'  

    def run(self, args, opts):  
        settings = get_project_settings()  
  
        for spider_name in self.crawler.spiders.list():  
            crawler = Crawler(settings)  
            crawler.configure()  
            spider = crawler.spiders.create(spider_name)  
            crawler.crawl(spider)  
            crawler.start()  
  
        self.crawler.start()  
    '''def run(self, args, opts):
        spider_list = self.crawler_process.spiders.list()
        for name in args or spider_list:
            self.crawler_process.crawl(name, **opts.__dict__)
        self.crawler_process.start()# 运行时，直接原来运行scrapy crawl spider_name的地方输入scrapy 和此文件名即：scrapy run '''