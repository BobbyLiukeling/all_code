import requests
import re

def getHTMLText(url):
    try:
        r=requests.get(url,timeout=10)
        r.raise_for_status()
        r.encoding=r.apparent_encoding
    except:
        return "it is fail"
    return r.text


def parsePage(ilt,Html):
    
        plt=re.findall(r'\"view_price\"\:\"[\d\.]*\"',Html)
        tlt=re.findall(r'"raw_title"\:\".*?"',Html)
        off=re.findall(r'"view_fee"\:\"[\d.]*"',Html)
        
        for i in range(len(plt)):
            price=eval(plt[i].split(":")[1])#eval 去掉双引号
            title=eval(tlt[i].split(":")[1])
            fee=eval(off[i].split(":")[1])
            ilt.append([price,title,fee])
    

def printGoodsList(ilt):
    tplt="{0:^10}{1:^15}{2:^15}{3:^30}"
    print(tplt.format("序号","价格","优惠","商品名称"))
    count=1
    for i in ilt:
        print(tplt.format(count,i[0],i[2],i[1]))
        count=count+1
    

def main():
    goods="书包"
    depth=5
    url_status="http://s.taobao.com/search?q="+goods
    infolist=[]
    for i in range(depth):
        try:
            url=url_status+"&s="+str(44*i)#tr(44*i):在淘宝上每个页面会显示44个商品，每个链接最后都会加上这样的相关数字
            html=getHTMLText(url)
            parsePage(infolist,html)
        except:
            continue

    printGoodsList(infolist)
    print("lalala")

main()