# -*- encoding: utf-8 -*-
# @author : bobby
# @time : 2020/2/17 12:27

# sentiment.marshal

from snownlp import sentiment
import time


start = time.time()
sentiment.train('neg.txt','pos.txt')
sentiment.save('sentiment.marshal.3')
end = time.time()
print(start - end)