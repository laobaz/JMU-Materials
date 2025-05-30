#if
name=('fuck','your','mother')
for names in name:
    if names == 'your':
        print(names.upper())
    if names != 'fuck':
        print(names.lower())
    else :
        print(names.title())

#'='可解读为“将变量car 的值设置为'au' ”。'=='是发问；对于❷处的代码，可解读为“变量car 的值是'bmw' 吗？”
#不相同 ！=
# 检查多个条件 and
age_1=18
age_2=22
#if age_2>22 and age_1<=18:
    #print('ture')
if age_1>=18 or age_2>=18:
    print('true')
age_1=11
age_2=12
if age_1>=18 or age_2>=18:
    print('false')
#检查特定值是否不包含在列表中  not in
name_not ='ok'
if name_not not in name:
    print('true')
#布尔表达式
car = 'subaru'
print("Is car == 'subaru'? I predict True.")
print(car == 'subaru')#返回true or false
print("\nIs car == 'audi'? I predict False.")
print(car == 'audi')
#else if ==elif
age= 12
if age<4:
    print('freedom')
elif age>=4 and age<=12:
    print('past')
else:
    print("amolst")
age=45
if age<4:
    price=0
elif age<=12:
    price=5
elif age<65:
    price=10
elif age>=65:
    price=5
print(price)

#测试多次多个if
age= 12
if age<4:
    print('freedom')
if age>=4 and age<=12:
    print('past')
if age>0:
    print("amolst")
add=[]
if add:#存在元素时执行
    print('have')
else:
    print('not')
#多个元素，多列表
available_toppings = ['mushrooms', 'olives', 'green peppers', 'pepperoni', 'pineapple', 'extra cheese']
requested_toppings = ['mushrooms', 'french fries', 'extra cheese']
for requested_topping in requested_toppings:
    if requested_topping in available_toppings:#多列表对比....
        print("Adding " + requested_topping + ".")
    else:
        print("Sorry, we don't have " + requested_topping + ".")
print("\nFinished making your pizza!")
