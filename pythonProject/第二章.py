print(chr(0b100111001011000))
print(ord('乘'))
name ='fuck'
fuck="fuck"
print('name')
print('fuck')
print('标识', id(name))
print('类型',type(name))
print('值',name)
message = "Hello Python Crash Course reader!"
print(message)
names='fuck'
print(names.title())#首字母大写 每个连续字母的首字符
print(names.upper())#全大写
print(names.lower())#全小写
frist_name='fuck'
last_name='you'
ok_name=frist_name+' '+last_name#' '是加一个空格
print(ok_name)
print( 'bitch'+' '+ok_name.title()+'!')
#找出字符串开头和末尾多余的空白。要确保字符串末尾没有空白，可使用方法rstrip()
namex="fuck     "
#namex.rstrip()清除但不保留
namex=namex.rstrip()
print(namex)
#你还可以剔除字符串开头的空白，或同时剔除字符串两端的空白。为此，可分别使用方法lstrip() 和strip() ：
namec='    fuck'
namec=namec.lstrip()
print(namec)
namev='  fuck   '
namev=namev.strip()
print(namev)
namet="'fuck '   "#“''""
namet=namet.rstrip()
print(namet)
print('Albert Einstein oncesaid,“Apersonwho never madea mistake never tried anything new.”')
#**乘方
print(6**2)
#函数str()输入字符串
age=23
print('happy '+str(age)+'rd brithday')
print(3/2)
