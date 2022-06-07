import requests
from bs4 import BeautifulSoup
url = "https://book.douban.com/top250"  # 要爬取的网页
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36'
}  #  headers是请求头的意思
req = requests.get(url, headers=headers)
print(req.status_code)  # res1.status_code是状态码的意思
#  输出 200, 则表明我们的步骤正确

soup = BeautifulSoup(req.text, 'html.parser')
#print(soup)

pl2s = soup.find_all('div', class_='pl2')  # class=用class_=表示
#print(pl2s)

list_1 = []
for pl2 in pl2s:
    item = pl2.find('a')
    name = item['title']
    list_1.append(name)

print(list_1)

