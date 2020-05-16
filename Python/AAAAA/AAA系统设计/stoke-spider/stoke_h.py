import requests
from bs4 import BeautifulSoup as bf
import xlwt
from spider import *
#get网站
'''
def request_stoke(url):
    try:
        response=requests.get(url)
        if response.status_code==200:
            return response.text
    except requests.RequestException:
        return None
'''
#存储到excel
#日期	开盘价	最高价	最低价	收盘价	涨跌额	涨跌幅(%)	成交量(手)	成交金额(万元)	振幅(%)	换手率(%)
def save_to_excel(sheet,html,n):
    #开始爬虫
    soup=bf(html,'lxml')
    trs=soup.find(class_='table_bg001 border_box limit_sale').find_all('tr')
    for tr in trs:
        tds=tr.find_all('td')
        td=[x for x in tds]
        if len(td)>=1:
            for m in range(0,len(td)):
                if m not in [0,7,8]:
                    sheet.write(n,m,float(td[m].text))
                else:
                    sheet.write(n,m,td[m].text)
            n=n+1
    return n

def history_data(num,year):
    n=1
    book=xlwt.Workbook(encoding='utf-8',style_compression=0)
    sheet=book.add_sheet('stoke',cell_overwrite_ok=True)
    #日期	开盘价	最高价	最低价	收盘价	涨跌额	涨跌幅(%)	成交量(手)	成交金额(万元)	振幅(%)	换手率(%)
    sheet.write(0,0,'日期')
    sheet.write(0,1,'开盘价')
    sheet.write(0,2,'最高价')
    sheet.write(0,3,'最低价')
    sheet.write(0,4,'收盘价')
    sheet.write(0,5,'涨跌额（%）')
    sheet.write(0,6,'涨跌幅（%）')
    sheet.write(0,7,'成交量（手）')
    sheet.write(0,8,'成交金额（万元）')
    sheet.write(0,9,'振幅（%）')
    sheet.write(0,10,'换手率（%）')
    #当年所有数据
    for season in range(1,4):
        url='http://quotes.money.163.com/trade/lsjysj_'+str(num)+'.html?year='+str(year)+'&season='+str(season)
        html=request_stoke(url)
        n=save_to_excel(sheet,html,n)+1
    book.save(get_name(num)+'.xls')

if __name__ == '__main__':
    num=601318
    history_data(num,2019)

