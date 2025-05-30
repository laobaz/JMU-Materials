#函数def
def name():
    print('fuck')
name()
#传递信息u
def name(username):#形参
    print('fuck '+username.title())
name('mother')#实参
#位置实参
def name(action,uername):
    print(action.title())
    print(uername)
name('fuck','mother')
#反复调用
name('fuck','father')
#关键实参
name(uername='mother',action='fuck')
#默认值
def name(action,username='mother'):
    print(action+username)
name(action='fuck')
#返回值
def name(action='fuck',username='mother'):
    right=action+username
    return right
names=name()#无法直接带出name的结果，要建立新变量
print(names)
#让实参变成可选的
#建立一个空字符串，用分支
def name(action,username,who=''):
    if who:
        full_name=action+' '+who+' '+username
    elif who!='':
        full_name=action+' '+username
    return full_name
names=name('fuck','mother','your')
print(names)
#返回字典
def name(action,username):
    names={'frist':action,'last':username}#不能加‘’会定义成字符串
    return names
namess=name('fuck','mother')
print(namess)
#while函数
def name(action,username):
    full_name=action+' '+username#在这边修改有效
    return full_name
while True:
    a_name=input('action')
    u_name=input('username')
    names=name(a_name,u_name)
    print(names)


