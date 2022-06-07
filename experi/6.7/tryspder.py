from ast import Num
from urllib.request import urlopen, Request
from bs4 import BeautifulSoup
import random


class DBTop250_Spider():
    url = r"http://book.douban.com/top250?start="
    page_num = 0
    top_num = 1
    headers = [
        {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:34.0) Gecko/20100101 Firefox/34.0'},
        {'User-Agent': 'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'},
        {
            'User-Agent': 'Mozilla/5.0 (Windows NT 6.2) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.12 '
                          'Safari/535.11'},
        {'User-Agent': 'Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; Trident/6.0)'},
        {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:40.0) Gecko/20100101 Firefox/40.0'},
        {
            'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu '
                          'Chromium/44.0.2403.89 Chrome/44.0.2403.89 Safari/537.36'}]
    file_path = "books"

    def Parse_Page(self):
        req = Request(self.url+str(self.page_num * 25), headers=random.choice(self.headers))
        page = urlopen(req).read()
        bsObj = BeautifulSoup(page, "html.parser")
        books_items = bsObj.find_all("a")
        for item in books_items:
            if 'title' in item.attrs:
                self.Parse_Book(item.attrs['href'])
                self.top_num += 1
        self.page_num += 1

    def Parse_Book(self, book_url):
        print("top" + str(self.top_num))
        print("book_url is: " + book_url)
        try:
            book_request = Request(book_url, headers=random.choice(self.headers))
            book_html = urlopen(book_request).read()
            book_bsObj = BeautifulSoup(book_html, "html.parser")
            book_title = book_bsObj.h1
            book_info = book_bsObj.find("div", {"id": "info"})
            intro = book_bsObj.find_all("div", {"class": "intro"})
            if intro[0].get_text().find("展开全部") != -1:
                book_intro = intro[1]
                if intro[2].get_text().find('展开全部') != -1:
                    author_intro = intro[3]
                else:
                    author_intro = intro[2]
            else:
                book_intro = intro[0]
                if intro[1].get_text().find('展开全部') != -1:
                    author_intro = intro[2]
                else:
                    author_intro = intro[1]
            with open(self.file_path + '/Top' + str(self.top_num) + '.txt', 'w', errors='ignore') as f:
                f.write(book_title.get_text().strip() + '\n')
                info_text = book_info.get_text().split(' ')
                for info in info_text:
                    if info != '\n' and info != '':
                        f.write(info.strip())
                f.write("\n\n内容简介: ")
                f.write(book_intro.get_text())
                f.write("\n\n作者简介: ")
                f.write(author_intro.get_text())
        except Exception as e:
            if hasattr(e, "reason"):
                print("Reason: " + e.reason)


sp = DBTop250_Spider()
for i in range(1, 200):
    sp.Parse_Page()
print("ok")
