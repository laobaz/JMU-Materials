print(777)
#   这是一条批注.......
#输出字符
print('hello world')
print('hello world')
print('hello','world','python')
#将文件输出地址
fp=open('D:/text.txt','a+')
print("hello world",file=fp)
fp. close()
#转义字符
print('hello\nworld')#\n 换行
print('hello\tworld')#\t 一个字符 ==4个字母
print('hello\bwolrd')#\b退一个字符
print('hello\rworld')#\r回车....world覆盖hello
print('http:\\\\baidu.com')#\\只会输出一个\
print('老师说：\'大家好\'')#使用\表示不是分隔符
#园字符==不希望字符串中的转义字符起作用。在字符串之前加R或r
print(R'hello\nworld')
#最后一格不能是反斜杠\
print('hello wolrd\\')