import turtle as t

r = 20
head = 90
for i in range(3):
    t.seth(head)
    t.circle(r)
    r = r + 20
r = 20
head = -90
for i in range(3):
    t.seth(head)
    t.circle(r)
    r = r + 20
t.done()
