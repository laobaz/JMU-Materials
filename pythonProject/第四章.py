#for循环  把列表存放在新列表中，一个个循环表达
magicican=('fuck','your','mother')
for magicians in magicican:#:不要忘了
    print(magicians)
#循环输出一个句子  间距非常重要**，同间距同函数
    print(magicians.title()+'your mother')
    print("I can't wait to see your next trick, " + magicians.title() + ".\n")
#在for 循环后面，没有缩进的代码都只执行一次，而不会重复执行。
#创建数值列表
#range()这是你在编程语言中经常看到的差一行为的结果。函数range()
# 让Python从你指定的第一个值开始数，
# 并在到达你指定的第二个值 后停止，因此输出不包含第二个值
for point in range(1,5):#in 从哪里
    print(point)
#建立数字列表
# 要创建数字列表，可使用函数list() 将range() 的结果直接转换为列表。
# 如果将range() 作为list() 的参数，输出将为一个数字列表。
points = list(range(1,6))  #list 一行排列
print(points)
pointx=range(1,5)#没有list 就是一个字符串
print(pointx)
#累加(1,11,累加量)
pointt=list(range(2,10,2))
print(pointt)
#立方
name=[]#使用空列表存储结果
for value in pointt:
    square=value**2
    name.append(square)
print(name)
#统计
fuck=max(name)
print(fuck)
fuck=min(name)
print(fuck)
fuck=sum(name)
print(fuck)
#列表合体
square=[value**2 for value in range(1,11)]#用【】穿
print(square)
#切片输出特定元素[a:b]a到b,a不出
namet=['fuck','you','mother','ok','?']
print(namet[0:3])
#最后几个 -n
print(namet[-3:])
for namex in namet[0:3]:
    print(namex+'\n')#换行
#复制列表[:]复制后的列表无关系
#用namez=namet时 会有串联关系
namez=namet[:]
print(namez)
#元组 无法改变
#由于试图修改元组的操作是被禁止的，因此Python指出不能给元组的元素赋值
#但可以重新定义
pointi=(100,233)
print(pointi[0])
print(pointi[1])
print(pointi)#返回是字符串
for pointis in pointi:
    print(pointis)#返回是数字

