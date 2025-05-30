#字典....查询   使用{}
alien_0={'color':'green','point':'5'}
print(alien_0['color'])#(     [ '   ' ])
print(alien_0['point'])
new_points=alien_0['point']
print('you need to earn '+alien_0['point']+'.')
print('you earned '+new_points+'.')
#添加键 — 值对 添加 元素
alien_0['x_position']=0
alien_0['y_position']=25
print(alien_0)
#创建一个空字典
alien_1={}
alien_1['x_position']=0
alien_1['y_position']=25
print(alien_1)
#修改字典中的值
alien_0['color']='yellow'
print(alien_0)
alien_2={'x_position':0,'y_position':25,'speed':'medium'}
if alien_2['speed']=='slow':
    x_in=1
elif  alien_2['speed']=='medium':
    x_in=2
else:
    x_in=3
alien_2['x_position']=alien_2['x_position']+x_in
print('new x '+str(alien_2['x_position'])+'!')
# 删除键  — 值对 del
del alien_0['point']
print(alien_0)
#由类似对象组成的字典
favorite={
    'fuck':'c',
    'you':'python',
    'mother':'java'
}
print(favorite['fuck'])
#遍历所有的键—值对
for key,value  in   favorite.items():    #列表的先后表达
    print('\nkey'+key)
    print('value'+value)
#遍历字典中的所有键  keys()  #key为 键  value 内容
for name in favorite.keys():
    print(name.title())
friends=['fuck','you']
for name in favorite.keys():
    if name in friends:#一个元素用等于，，多个用 in
        print(name.title())
# 按顺序遍历字典中的所有键 sorted
for name in sorted(favorite.keys()):
    print(name.title()+' thank you for taking the poll.')
#遍历字典中的所有值 value()
for name in favorite.values():
    print(name.title())
# 嵌套
alien_0 = {'color': 'green', 'points': 5}
alien_1 = {'color': 'yellow', 'points': 10}
alien_2 = {'color': 'red', 'points': 15}
aliens=[alien_0,alien_1,alien_2]#用[]
for alien in aliens:
    print(alien)
#建立多字典
alien=[]
for alien_number in range(30):
    alien_new={'color':'blue','speed':'slow'}
    alien.append(alien_new)
for aliens in alien[0:2]:
    aliens['color']='yellow'
    aliens['speed']='10'
for aliens in alien[1:4]:
    aliens['color']='red'
for aliens in alien[0:6]:
    print("\n"+str(aliens))
#在字典中存储列表
alien = {
    'color':['red','green'] ,#用循环表达
    'speed':'slow'

}
for colors in alien['color']:
    print(colors)
#在字典中存储字典
favorite={
    'favorites':{
       'fuck':'c',
       'you':'puthon',
       'mother':'java'

},
    'favoritess':{
        'fuck':'c',
        'you':'puthon',
        'mother':'java'
    }
}
for fa,vo in favorite.items():
    print(fa)
    fas=vo['mother']
    print(fas)
    