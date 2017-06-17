# encoding: utf-8
import requests
import re
from bs4 import BeautifulSoup
import time


class News:
    def __init__(self, title, time, type, content):
        self.title = title  # 新闻标题
        self.time = time  # 新闻时间
        self.type = type  # 新闻类别
        self.content = content  # 新闻内容


def getList(url):  # 获取新闻链接地址
    li = requests.get(url)
    res = r'url":"http:.*?.html'  # 正则表达式获取链接地址
    urls = re.findall(res, li.text)
    for i in range(len(urls)):
        urls[i] = urls[i][6:]
    return urls


def getNews(url):  # 获取新闻内容
    url = url[:-5] + "_0.html"  # 处理链接获取全文
    ss = requests.get(url)
    soup = BeautifulSoup(ss.text, "html.parser")  # 获取新闻内容，注意编码
    title = soup.title.string[:-6].encode('utf-8')
    time = soup.find("div", "about").contents[0][9:].encode('utf-8')
    #    type = soup.find("div","position lBlue").contents[3].string.encode('utf-8')
    content = soup.find("div", "content").get_text()[1:-1].encode('utf-8')
    news = News(title, time, type, content)
    return news


def saveAsTxt(url, news):  # 保存新闻链接内容
    file = open('news.txt', 'a')
    file.write("标题:" + news.title.decode('UTF-8', 'ignore') +
               "\t时间:" + news.time.decode('UTF-8', 'ignore') +
               "\t链接:" + url +
               "\n")

start = time.clock()
sum = 0
for i in range(1, 40):
    wangzhi = "http://3g.163.com/touch/article/list/BA8J7DG9wangning/%s-40.html" % i
    urls = getList(wangzhi)
    sum = sum + len(urls)
    #    print "当前页解析出 %s 条" %len(urls)
    j = 1
    for url in urls:
        print ("正在读取第%s页第%s/%s条:%s" % (i, j, len(urls), url.encode('utf-8')))
        news = getNews(url)
        saveAsTxt(url, news)
        j = j + 1
end = time.clock()
print ("共爬取%s条新闻，耗时%f s" % (sum, end - start))
