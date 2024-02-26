f = open("C:/Users/24464/Downloads/hamlet.txt",'r')
txt = f.read()
txt = txt.lower()
d = {}

for s in '!"#$%&()*+,-./:;<=>?@[\\]^_‘{|}~':
    txt = txt.replace(s,'')
list = txt.split()

for i in list:
    if i not in '\n':
        d[i] = d.get(i,0) + 1

sort = sorted(d.items(),key=lambda x:x[1],reverse=True)
for k in range(10):     #相比之下 就比之前要多了一个10次遍历
    print(sort[k][0])    #因为已经k是是数字0123..那么后面只需要索引每个字符的位置（1）就行
f.close()