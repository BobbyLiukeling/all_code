# -*- coding : utf-8 -*-
__author__ = "bobby"

from scrapy.command import ScrapyCommand
from scrapy.utils.project import get_project_settings

class Command(ScrapyCommand):

  requires_project=True

  def syntax(self):
    return "[options]"

  def short_desc(self):
    return "Run all of the spiders"

  def run (self,args,opts):
    spider_list = self.crawler_process.spiders.list()
    for name in spider_list:
      self.crawler_process.crawl(name,**opts.__dict__)

    self.crawler_process.start()