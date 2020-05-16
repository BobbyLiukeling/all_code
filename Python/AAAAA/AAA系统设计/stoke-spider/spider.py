import requests
from bs4 import BeautifulSoup as bf
#爬取网站
def request_stoke(url):
    try:
        response=requests.get(url)
        if response.status_code==200:
            return response.text
    except requests.RequestException:
        return None
#爬取股票名称
def get_name(num):
    url='http://quotes.money.163.com/trade/lsjysj_'+str(num)+'.html?year=2019&season=1'
    html=request_stoke(url)
    soup=bf(html,'lxml')
    name=soup.find(class_='name').find('a').string
    return name
