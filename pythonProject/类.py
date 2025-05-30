class dog():
    def __init__(self,name,age):
        self.name=name
        self.age=age
        self.fuck=0
    def sit(self):
        print(self.name.title()+" sit")
    def longs_name(self):
        long_name=(self.name.title()+self.name.title()+self.name.title())
        return long_name.title()
    def update_fuck(self,chance):
        self.fuck=chance
    def increase_fuck(self,chances):
        self.fuck+=chances
#复制
class new(dog):
    def __init__(self,name,age):
        super().__init__(name,age)#把dog中的所以函数都复制一次

        

my_new_dog=new("fuck",6)
printf(my_new_dog.name.title)
my_dog= dog('fuck',6)#类赋给my_dog,和结构一样
print("my dog name is "+my_dog.name.title())
my_dog.sit()
print(my_dog.longs_name())
print(str(my_dog.fuck)-12)

