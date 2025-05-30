'''
f=open("text.txt","w")#w为写入文件  “w“（写入）
#r默认 r模式  指针在头，只读，不写
#w写入 会覆盖
#a 追加
#r+
f.write("fuck your mother")#写入

f.close()#关闭文件
'''
'''
f=open("text.txt","r")
#一个个字符读
content=f.read(5)#从5开始
print(content)
content=f.read(5)
print(content)
f.close()
'''
'''
f=open("text.txt")
content=f.readlines()#形成列表一次性读取
#print(content)
i=1
for temp in content:
    print("%d:%s"%(i,temp))#%d 数字 %d字符串 %占位
    i+=1

f.close()
'''
'''
f=open("text.txt")
content=f.readline()
print("1:%s"%content)
f.close()
print("2:%s"%content)
f.close()
'''
'''
for x in range(1,10):
    print('\t')
    for y in range(1,x+1):
        result = x * y
        print("%d * %d = %d"%(x,y,result),'\t')
'''
'''
def printline():
     print("-"*30)
def printlineline(num):
    i=0
    while i<num:
        printline()
        i+=1
printlineline(3)
'''
'''
def sum(a,b):
    return a+b
def sumx(a,b):
    sums=sum(a,b)
    return sums/3.0
print(sumx(2,3))
'''
# '''
# filename='fuck.txt'
# with open(filename,'w')as file_object:
#     file_object.write("fuck your mother.\n")
#     file_object.write("fuck your father.\n")
# with open(filename,'a')as file_object:
#     file_object.write('fuck you')
# '''
# print(5/0)
'''
try:
    print(5/0)
except ZeroDivisionError:
    print("你除0,你除你妈呢".strip())
print("Give me two numbers, and I'll divide them.")
print("Enter 'q' to quit.")
while True:
    first_number = input("\nFirst number: ")
    if first_number == 'q':
       break
    second_number = input("Second number: ")
    if second_number=='q':
        break
    else:
          try:answer = int(first_number) / int(second_number)
          except ZeroDivisionError:
                 print("You can't divide by 0!")
          else:
               print(answer)
'''
# 计算单词数目split()以空格为一个单位把分成一个个列表
'''
fliename = 'text.txt'
with open(fliename)as flie_obj:
    content=flie_obj.read()
words=content.split()
lens=len(words)
print(lens)
'''
# import json
# name=['fuck','your','mother']
# filename='text.txt'
# with open(filename,'w')as file_obj:
#     json.dump(name,file_obj)#写入
# with open(filename)as file_obj:
#      names=json.load(file_obj)#读取
# print(names)
# import json
# uersname=input("what's your name?")
# filename='text.txt'
# with open(filename,'w')as f_obj:
#     json.dump(uersname,f_obj)
# with open(filename)as f_obj:
#      name=json.load(f_obj)
# print(name)

import json


def get_name():
    filename = 'new.txt'
    try:
        with open(filename) as f_obj:
            username = json.load(f_obj)
    except FileNotFoundError:
        return None
    else:
        return username


def use() :
    uername = get_name()

    if uername:
        print("Welcome back, " + uername + "!")
    else:
        uername = input("what's your name?")
        filename = 'new.txt'
        with open(filename,'a') as f_obj:
            json.dump(uername, f_obj)

use()
# import json
# def get_stored_username():
#     """如果存储了用户名，就获取它"""
#     filename = 'username.json'
#     try:
#         with open(filename) as f_obj:
#             username = json.load(f_obj)
#     except FileNotFoundError:
#         return None
#     else:
#         return username
# def greet_user():
#      username = get_stored_username()
#      if username:
#          print("Welcome back, " + username + "!")
#      else:
#       username = input("What is your name? ")
#       filename = 'username.json'
#       with open(filename, 'w') as f_obj:
#           json.dump(username, f_obj)
#           print("We'll remember you when you come back, " + username + "!")
# greet_user()
