# -*- coding: utf-8 -*-
import sys
import re
from bs4 import BeautifulSoup
import requests
import urllib.parse
from PyQt5.QtWidgets import (QPushButton,QWidget, QLabel, QLineEdit, QTextEdit, QGridLayout,QApplication)
from PyQt5.QtGui import QIcon
from spider import *
from stoke_sql import *
from stoke_h import *
from plot import *
class Example(QWidget):
    def __init__(self): # 初始化
        super().__init__()
        self.initUI()

    def initUI(self):
        #GUI布局及控件放置
        search_num = QLabel("请输入需要检索的股票代码：")
        item_num=QLineEdit()
        search_year=QLabel("请输入需要检索的年份：")
        item_year=QLineEdit()
        btn1=QPushButton("开始搜索股票", self)
        btn2=QPushButton("生成数据统计图", self)
        btn3=QPushButton("导入Excel", self)
        btn4=QPushButton("导入数据库", self)
        btn5=QPushButton("清空", self)
        result_label=QLabel("执行结果：")
        search_result = QTextEdit()
        grid = QGridLayout()
        grid.setSpacing(5)
        grid.addWidget(search_num,1,0)
        grid.addWidget(item_num,1,1)
        grid.addWidget(search_year,2,0)
        grid.addWidget(item_year,2,1)
        grid.addWidget(btn1,3,0)
        grid.addWidget(btn2,3,1)
        grid.addWidget(btn3,4,0)
        grid.addWidget(btn4,4,1)
        grid.addWidget(btn5,5,0)
        grid.addWidget(result_label,6,0)
        grid.addWidget(search_result,6,1)
        self.setLayout(grid)

       
        def searching():
            search_result.setText("股票名："+get_name(item_num.text()))
        btn1.clicked.connect(searching)

        def sql():
            save_sql(item_num.text(),item_year.text())
            search_result.setText("完成录入数据库表格"+get_name(item_num.text()))
        btn4.clicked.connect(sql)
        def excel():
            history_data(item_num.text(),item_year.text())
            search_result.setText("完成录入文件"+get_name(item_num.text())+".xls")
        btn3.clicked.connect(excel)
        def plot():
            stoke_plot(item_num.text(),item_year.text())
            search_result.setText("完成创建"+get_name(item_num.text())+"收盘价图")
        btn2.clicked.connect(plot)
        def clear():
            search_result.setText("")
            item_num.setText("")
            item_year.setText("")
        btn5.clicked.connect(clear)
        
        self.setWindowIcon(QIcon('icon.jpg'))
        self.setGeometry(500, 200, 700, 550)
        self.setWindowTitle("股票数据处理系统")
        self.show()



if __name__ == "__main__":
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
