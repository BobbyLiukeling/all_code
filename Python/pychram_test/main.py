# -*- coding: utf-8 -*-
__author__ = "bobby"

from scrapy.cmdline import execute
import sys
import os

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
#print(os.path.abspath(__file__)) #当前目录
#print(os.path.dirname(os.path.abspath(__file__)))#当前目录父目录
execute(["scrapy","crawl","douban"])

