import turtle
def drawSnake(rad,angle,len,nechrad):
    for i in range(len):
        turtle.circle(rad,angle) #rad是圆形轨迹的半径，angle是角度
        turtle.circle(-rad,angle)
    turtle.circle(rad,angle/2)
    turtle.fd(rad)#向前直线爬行距离
    turtle.circle(nechrad+1,180) 
    turtle.fd(rad*2/3)

def main():
    turtle.setup(1200,600,0,0)
    pythonsize=30 #蛇体的宽度
    turtle.pensize(pythonsize)
    turtle.pencolor("yellow")#表示颜色
    turtle.seth(-20)#运行时的起始方向
    drawSnake(40,80,5,pythonsize/2)

main()
