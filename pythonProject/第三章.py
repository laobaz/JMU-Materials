###列表
#[]会把变量=后的所以东西都输出,
bicycle=['fuck','your','monther']
print(bicycle)
#列表==数组
#‘’会把逗号隔开的的东西分成一个个数组【0】【1】【2】....
#通过将索引指定为- ，可让Python返回反向访问最后一个列表元素
print(bicycle[-2].title())
#列表就是一个变量不加‘’
print('i have a '+bicycle[2].title()+'!')
#修改列表元素和数组一样
bicycle[0]='love'
print(bicycle)
#添加元素append() 会自动加,要有‘’
bicycle.append('and')
print(bicycle)
#建立空列表用append加元素
#修改列表元素insert()加在元素前面
bicycle.insert(0,'love')
print(bicycle)
#从列表中删除元素 \
# 1.del()
del bicycle[0]
print(bicycle)
#2.pop()  建立一个被删除元素的列表 转移
popped_bicycle=bicycle.pop(3)#popped_bicycle存储被删的元素
print(bicycle)
print(popped_bicycle)
print('i have a '+popped_bicycle.title()+'!')
#根据值删除元素remove  转移元素到列表里和pop相似
#方法remove() 只删除第一个指定的值。如果要删除的值可能在列表中出现多次，就需要使用循环来判断是否删除了所有这样的值。
too= 'love'
bicycle.remove(too)
print(bicycle)
print(too)
# 使 sort() 对列表进行永久性排序按字母排列
bicycle.sort()
print(bicycle)
#反向
bicycle.sort(reverse=True)
print(bicycle)
#临时排列sorted
print(sorted(bicycle))
print(bicycle)
#倒着打印列表reverse()不是指按与字母顺序相反的顺序排列列表元素，而只是反转列表元素的排列顺序
bicycle.reverse()
print(bicycle)
# 确定列表的长度len()Python计算列表元素数时从1开始，因此确定列表长度时，你应该不会遇到差一错误
print(len(bicycle))


