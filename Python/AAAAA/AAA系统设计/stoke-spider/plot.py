# -*- coding: utf-8 -*-
from spider import *
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
def stoke_plot(num,year):
    dates=[]
    fins=[]
    for season in range(1,4):
        url='http://quotes.money.163.com/trade/lsjysj_'+str(num)+'.html?year='+str(year)+'&season='+str(season)
        html=request_stoke(url)
        soup=bf(html,'lxml')
        trs=soup.find(class_='table_bg001 border_box limit_sale').find_all('tr')
        for tr in trs:
            tds=tr.find_all('td')
            td=[x for x in tds]
            if len(td)>=1:
                if td[0]!=''and td[4]!=0:
                    dates.append(td[0].text)
                    fins.append(float(td[4].text))
    data= dict(map(lambda x,y:[x,y],dates,fins))
    dates=sorted(data)
    fins=[]
    for date in dates:
        fins.append(data[date])
    font =FontProperties(fname=r"SimHei.ttf", size=14)
    fig,ax = plt.subplots(1,1)
    plt.plot(dates,fins)
    for label in ax.get_xticklabels():
        label.set_visible(False)
    for label in ax.get_xticklabels()[::20]:
        label.set_visible(True)
    plt.xticks(rotation=45)
    plt.xlabel("日期", fontproperties=font)
    plt.ylabel("收盘价", fontproperties=font)
    plt.title(str(year)+"年"+get_name(num)+"收盘价历史数据", fontproperties=font)
    plt.tight_layout()
    plt.savefig("./pic/"+str(year)+"年"+get_name(num)+"收盘价波历史数据.png")
    
    plt.show()
if __name__ == "__main__":
    stoke_plot(601318,2019)

