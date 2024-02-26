import jieba
txt = open("C:/Users/24464/Downloads/hamlet.txt").read()
words = jieba.lcut(txt)
dictionary = {}
for word in words:
    dictionary[word] = dictionary.get(word, 0) + 1
maxcount = 0
maxword = ""
for key in dictionary:
    if len(key) >= 2 and dictionary[key] > maxcount:
        maxcount = dictionary[key]
        maxword = key
    if len(key) >= 2 and dictionary[key] == maxcount and key > maxword:
        maxword = key
print(maxword)
