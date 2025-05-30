class myClass(object):
    def __init__(self):
        self.language="china"
    def __del__(self):
        return 0
    def __str__(self):
        print(self.language)
    def __set_name__(self, owner, name):
        return 0


classes = myClass()


class myclasses(myClass):
    def __init__(self):
        self.language="english"

    def fun(self):
        myClass.__init__(self)


from abc import ABCMeta, abstractmethod


class soldiers(object):
    @abstractmethod  # 定义抽象函数
    def displaySkill(self):
        pass


# 突击士兵
class assaultSoldier(soldiers):
    def displaySkill(self):
        print('施展技能：快、猛、狠')


# 医疗兵
class medicSoldier(soldiers):
    def displaySkill(self):
        print('施展技能：救护伤员')


# 工兵
class engineerSoldier(soldiers):
    def displaySkill(self):
        print('施展技能：排雷')


#
class Person(object):
    def showSkill(self, soldier):
        soldier.displaySkill()


assaultsoldier = assaultSoldier()
medicsoldier = medicSoldier()
engineersoldier = engineerSoldier()
person = Person()
person.showSkill(assaultsoldier)
person.showSkill(medicsoldier)
person.showSkill(engineersoldier)
# 施展技能：快、猛、狠
# 施展技能：救护伤员
# 施展技能：排雷




#公有属性
class person(object):
    #类属性
    countNum = 0
    testnum = 20
    def __init__(self):
        person.countNum=person.countNum+1
per1 = person()
person.testnum +=5
per2 = person()
person.testnum +=5
per3 = person()
per3.testnum +=5            #不能通过 实例.属性名去修改公有属性,否则创建的是一个实例属性
print(per3.countNum)        #3   类属性可以通过实例.属性名 访问
print(person.countNum)      #3   类属性可以通过类名.属性名 访问
print(person.testnum)       #30
print(per3.testnum)         #35 新建了实例属性 testnum ，在公有属性值基础上加了5

print(person.age)           #实例属性 不能通过 类名.属性名 访问


class student(object):
    stuNum = 0  # 类属性

    def __init__(self, name):
        self.name = name  # 实例属性 访问
        student.addnum()  # 类方法 访问

    @classmethod  # 类方法
    def addnum(cls):
        cls.stuNum += 1  # 类属性

    @classmethod  # 类方法
    def getnum(cls):
        return cls.stuNum

    @staticmethod  # 静态方法，不能访问类对象方法和属性，也不能访问实例方法和属性
    def do_something():
        print("well done,every student !")


stu1 = student('xiaoming')
stu2 = student('xiaozhang')
stu3 = student('xiaowang')
stu4 = student('xiaodu')
# 类的方法 可以提供通过类、实例访问
print("total num:{}".format(student.getnum()))  # total num:4
print("total num:{}".format(stu4.getnum()))


# 静态方法 可以提供通过类、实例访问
student.do_something()  # well done,every student !
stu1.do_something()  # well done,every student !
stu2.do_something()  # well done,every student !