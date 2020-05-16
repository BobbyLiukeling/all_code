import glob
import os
import tensorflow as tf
import numpy as np

path = '../../datasets/lululu'
f = '../../datasets/file1.txt'


def read_writeFile(path, f):
    cate = [path + '/' + x for x in os.listdir(path)]
    f2 = open(f, 'a+')
    for idx, folder in enumerate(cate):
        for im in glob.glob(folder + '/*.jpg.txt'):
            f1 = open(im, 'r')
            for eachLine in f1:
                f2.write(eachLine)
                f2.write(' ' + str(idx + 1) + '\n')
            f1.close()


read_writeFile(path, f)
