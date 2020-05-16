#2018.01.09
#统计词频
#字典和turtle的使用
#来源：中国大学MOOC

import turtle

count=10 #显示出现频率前十的单词
date=[] #单词的词频Y轴
words=[] #单词数组X轴
yScale=6 #y轴放大倍数
xScale=50# X轴放大倍数




##################turtle begin################

#从点(x1,y1)到（x2,y2）绘制线段
def drawLine(t,x1,y1,x2,y2):
    t.penup()
    t.goto(x1,y1)
    t.pendown()
    t.goto(x2,y2)

#在坐标（x，y）处写字

def drawText(t,x,y,text):
    t.penup()
    t.goto(x,y)
    t.pendown()
    t.write(text)

def drawGraph(t):
    #绘制X,Y轴
    drawLine(t,0,0,560,0)
    drawLine(t,0,360,0,0)

    #X轴：坐标及描述
    for x in range(count):
        x=x+1 #向右移不画在原来的位置上
        drawText(t,x*xScale-4,-20,(words[x-1]))
        drawText(t,x*xScale-4,date[x-1]*yScale+10,date[x-1])
    drawBar(t)

#绘制一个柱体
def drawRectangle(t,x,y):
    x=x*xScale
    y=y*yScale
    drawLine(t,x-5,0,x-5,y)
    drawLine(t,x-5,y,x+5,y)
    drawLine(t,x+5,y,x+5,0)
    drawLine(t,x+5,0,x-5,0)

#绘制多个柱体
def drawBar(t):
    for i in range(count):
        drawRectangle(t,i+1,date[i])

###########turtle end################

#对文本的每一行计算词频
def processLine(line,wordCounts):
    #用空格替换标点符号
    line=replacePunctuations(line)
    #从每一行中获取每个词
    words =line.split()
    for word in words:
        if word in wordCounts:
            wordCounts[word]+=1
        else:
            wordCounts[word]=1

#用空格替换标点函数
def replacePunctuations(line):
    for ch in line:
        if ch in "~@#$%^&*()_-+=<>?/,.:;{}[]|\'""":
            line=line.replace(ch," ")
    return line

def main():
    #用户输入一个文件
    filename=input("enter n filename:").strip()
    infile=open(filename,"r")

    #建立用于计算词频的空字典
    wordCount={}
    for line in infile:
        processLine(line.lower(),wordCount)

    #从字典中获取数据对
    pairs=list(wordCount.items())

    #列表中的数据对交换位置，数据对排序
    items=[[x,y] for (y,x) in pairs]
    items.sort()

    #输出count个数词频结果
    for i in range(len(items)-1,len(items)-count-1,-1):
        print(items[i][1]+"\t"+str(items[i][0]))
        date.append(items[i][0])
        words.append(items[i][1])

    infile.close()

    #根据词频结果画出柱状图
    turtle.title("词频结果柱状图")
    turtle.setup(1300,700,0,0)
    t=turtle.Turtle()
    t.hideturtle()
    t.width(3)
    drawGraph(t)

#调用main函数
if __name__=="__main__":
    main()



