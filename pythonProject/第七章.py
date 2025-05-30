#用户输入input
meggage=input("fuck your mother,ok?")
print(meggage)
print('hello '+meggage)#实际输出的是输入的。
#分行
message='fuck your mother?'
message+='fuck your father?'
message=input(message)
print(message)
#使用 int() 来获取数值输入
#input得到的是字符串，不是数字
point=input('输入:')
point=int(point)
if point>=18:
    print(point+'fuck~~~!')
else:
    print('fuck~~~!')
#while循环
#让用户选择何时退出 quit
things=""
while things !='quit':
    things=input(message)
    print(things)
#使用标志
active=True
while active :#当他为false时停止。
    if things=='quit':
        active==False
    else:
        print(things)
#使用使 break 退出循环
while True :#当他为false时停止。
    if things=='quit':
        break
    else:
        print(things)
#在循环中使用 在 continue
#while True :#当他为false时停止。
    #if things=='quit':
       # continue#跳到下个循环
    #else:
       # print(things)
#删除包含特定值的所有列表元素
messages=['fuck','fuck','your','mother']
while 'fuck' in messages:
    messages.remove('fuck')
print(messages)
# 使用用户输入来填充字典
actives=True
resposes={}
while actives:
    name=input("name")
    respose=input('respose')
    resposes[name]=respose
    repeat=input('ok?')
    if repeat=='no':
        actives=False

for name ,respose in resposes.items():
    print(name+respose)
#在列表之间移动元素
old=['fuck','your','mother']
new=[]
while old:
    news=old.pop()
    new.append(news)
for newss in new:
    print(newss)