# 可参照编程模板，完善代码实现图形绘制，亦可以自行设计编码实现。
import turtle
turtle.fillcolor("yellow")
turtle.begin_fill()
for i in range(12):
    turtle.circle(200, 75)
    turtle.left(135)
turtle.end_fill()
turtle.hideturtle()
turtle.done()
