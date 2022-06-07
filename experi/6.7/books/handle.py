from operator import index
import re


name = []
auther = []
date = []
publisher =[]
price = []
type = []
isbn = []
desc = []

def str_handle(str_):
    return str_.split(':',1)[1].split()[0]

for i in range(1,10):
    with open("Top" + str(i) + '.txt','r') as file:
        content = file.read().splitlines()
        #print(content)
        name.append(content[0])
        auther.append(str_handle(content[1]))
        date.append(str_handle(list(filter(lambda x: re.match('出版年:*', x) != None, content))[0]))
        price.append(str_handle(list(filter(lambda x: re.match('定价:*', x) != None, content))[0]))
        #type.append(str_handle(list(filter(lambda x: re.match('丛书: *', x) != None, content))[0]))
        temp = list(filter(lambda x: re.match('丛书: *', x) != None, content))
        if temp:
            type.append(str_handle(temp[0]))
        publisher.append(content[content.index('出版社:')+1])
        desc.append(content[content.index('内容简介: ')+1])
        isbn.append(str_handle(list(filter(lambda x: re.match('ISBN*', x) != None, content))[0]))

print(name)
print(auther)
print(date)
print(publisher)
print(price)
print(type)
print(isbn)
#print(desc)



        