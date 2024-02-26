import turtle as t

t.colormode(255)
t.color(255, 215, 0)  # 设置颜色取值为金色（255,215,0）
t.begin_fill()
for x in range(8):  # 绘制8条线
    t.forward(200)
    t.left(225)
t.end_fill()
t.hideturtle()
t.done()
