

# 第一天

## 1 Qt简介

1.1 跨平台图形界面引擎

1.2 历史

1.2.1 1991  奇趣科技

1.3 优点

1.3.1 跨平台

1.3.2 接口简单，容易上手

1.3.3 一定程度上简化了内存回收

1.4 版本

1.4.1 商业版

1.4.2 开源版

1.5 成功案例

1.5.1 Linux桌面环境 KDE

1.5.2 谷歌地图

1.5.3 VLC多媒体播放器

1.5.4 …

## 2 创建第一个Qt程序

2.1 点击创建项目后，选择项目路径以及 给项目起名称

2.2 名称 -  不能有中文 不能有空格

2.3 路径 -  不能有中文路径

2.4 默认创建有窗口类，myWidget，基类有三种选择： QWidget 、QMainWindow、QDialog

2.5 main函数

2.5.1 QApplication a  应用程序对象，有且仅有一个

2.5.2 myWidget w;实例化窗口对象

2.5.3 w.show()调用show函数 显示窗口

2.5.4 return a.exec() 让应用程序对象进入消息循环机制中，代码阻塞到当前行

## 3 按钮控件常用API

3.1 创建 QPushButton * btn = new QPushButton

3.2 设置父亲  setParent(this)

3.3 设置文本  setText(“文字”)

3.4 设置位置  move(宽，高)

3.5 重新指定窗口大小  resize

3.6 设置窗口标题 setWindowTitle

3.7 设置窗口固定大小 setFixedSize

## 4 对象树

4.1 当创建的对象在堆区时候，如果指定的父亲是QObject派生下来的类或者QObject子类派生下来的类，可以不用管理释放的操作，将对象会放入到对象树中。

4.2 一定程度上简化了内存回收机制

## 5 Qt中的坐标



5.1 左上角为 0 ， 0 点

5.2 x以右为正方向

5.3 y以下为正方向

## 6 信号和槽

6.1 连接函数 ：connect

6.2 参数  

6.2.1 参数1  信号的发送者

6.2.2 参数2  发送的信号（函数地址）

6.2.3 参数3  信号的接受者

6.2.4 参数4  处理的槽函数 （函数的地址）

6.3 松散耦合

6.4 实现 点击按钮 关闭窗口的案例

6.5 connect(btn ,  &QPushButton::click , this , &QWidget::close );

## 7 自定义信号和槽

7.1 自定义信号

7.1.1 写到 signals下

7.1.2 返回 void

7.1.3 需要声明，不需要实现

7.1.4 可以有参数	，可以重载

7.2 自定义槽函数

7.2.1 返回void

7.2.2 需要声明 ，也需要实现

7.2.3 可以有参数 ，可以重载

7.2.4 写到 public slot下 或者public 或者全局函数

7.3 触发自定义的信号

7.3.1 emit 自定义信号

7.4 案例-下课后，老师触发饿了信号，学生响应信号，请客吃饭

## 8 当自定义信号和槽出现重载

8.1 需要利用函数指针 明确指向函数的地址

8.2 void( Teacher:: * tSignal )( QString ) = &Teacher::hungry;

8.3 QString 转成  char *   

8.3.1 .ToUtf8() 转为 QByteArray

8.3.2 .Data() 转为 Char *

8.4 信号可以连接信号 

8.5 断开信号  disconnect

## 9 拓展

9.1 信号可以连接信号

9.2 一个信号可以连接多个槽函数

9.3 多个信号可以连接同一个槽函数

9.4 信号和槽函数的参数 必须类型一一对应

9.5 信号和槽的参数个数  是不是要一致？信号的参数个数 可以多余槽函数的参数个数

9.6 信号槽可以断开连接  disconnect

## 10 Qt4版本写法

10.1 connect( 信号的发送者， 发送的信号SIGNAL( 信号) ，信号接受者， 槽函数SLOT(槽函数)  )

10.2 优点 参数直观

10.3 缺点 编译器不会检测参数类型

11 Lambda表达式

11.1 []标识符  匿名函数 

11.1.1 = 值传递

11.1.2 & 引用传递

11.2 () 参数 

11.3 {} 实现体

11.4 mutable 修饰 值传递变量 ，可以修改拷贝出的数据，改变不了本体

11.5 返回值[]() ->int {}





![信号和槽解析图](https://raw.githubusercontent.com/laobaz/tuba/master/%E4%BF%A1%E5%8F%B7%E5%92%8C%E6%A7%BD%E8%A7%A3%E6%9E%90%E5%9B%BE-1684415883224.png)

![Qt对象树](https://raw.githubusercontent.com/laobaz/tuba/master/Qt%E5%AF%B9%E8%B1%A1%E6%A0%91.png)

 ![Qt信号和槽 ](https://raw.githubusercontent.com/laobaz/tuba/master/Qt%E4%BF%A1%E5%8F%B7%E5%92%8C%E6%A7%BD%20.png)



![信号连接信号解析图](https://raw.githubusercontent.com/laobaz/tuba/master/%E4%BF%A1%E5%8F%B7%E8%BF%9E%E6%8E%A5%E4%BF%A1%E5%8F%B7%E8%A7%A3%E6%9E%90%E5%9B%BE-1684415861502.png)

![Qt5 模块](https://raw.githubusercontent.com/laobaz/tuba/master/Qt5%20%E6%A8%A1%E5%9D%97.png)



# 第二天

## 1 QMainWindow

```c++
1.1 菜单栏 最多有一个

1.1.1 QMenuBar * bar = MenuBar();

1.1.2 setMenuBar( bar ) 

1.1.3 QMenu * fileMenu = bar -> addMenu(“文件”)  创建菜单

1.1.4 QAction * newAction =  fileMenu ->addAction(“新建”); 创建菜单项

1.1.5 添加分割线 fileMenu->addSeparator();

1.2 工具栏 可以有多个

1.2.1 QToolBar * toolbar = new QToolBar(this);

1.2.2 addToolBar( 默认停靠区域， toolbar );  Qt::LeftToolBarArea

1.2.3 设置  后期停靠区域，设置浮动，设置移动

1.2.4 添加菜单项 或者添加 小控件

1.3 状态栏  最多一个

1.3.1 QStatusBar * stBar = statusBar();

1.3.2 设置到窗口中 setStatusBar(stBar);

1.3.3  stBar->addWidget(label);放左侧信息

1.3.4  stBar->addPermanentWidget(label2); 放右侧信息

1.4 铆接部件  浮动窗口  可以多个

1.4.1 QDockWidget 

1.4.2 addDockWidget( 默认停靠区域，浮动窗口指针)

1.4.3 设置后期停靠区域

1.5 设置核心部件  只能一个

1.5.1 setCentralWidget(edit);
```



## 2 资源文件

2.1 将图片文件 拷贝到项目位置下

2.2 右键项目->添加新文件 –>  Qt - > Qt recourse File  - >给资源文件起名

2.3 res 生成  res.qrc  

2.4 open in editor  编辑资源

2.5 添加前缀  添加文件

2.6 使用  “ : + 前缀名 + 文件名 ”

## 3 对话框

```c++
3.1 分类 ： 

3.1.1 模态对话框  不可以对其他窗口进行操作 阻塞

3.1.1.1 QDialog  dlg(this)

3.1.1.2 dlg.exec();

3.1.2 非模态对话框  可以对其他窗口进行操作

3.1.2.1 防止一闪而过 创建到堆区

3.1.2.2 QDialog * dlg = new QDialog(this)

3.1.2.3 dlg->show();

3.1.2.4 dlg2->setAttribute(Qt::WA_DeleteOnClose); //55号 属性

3.2 标准对话框 --  消息对话框

3.2.1 QMessageBox 静态成员函数  创建对话框

3.2.2 错误、信息、提问、警告

3.2.3 参数1  父亲 参数2  标题  参数3  显示内容 参数4  按键类型  参数5 默认关联回车按键

3.2.4 返回值 也是StandardButton类型，利用返回值判断用户的输入

3.3 其他标准对话框

3.3.1 颜色对话框  QColorDialog：：getColor 

3.3.2 文件对话框  QFileDialog：：getOpenFileName(父亲，标题，默认路径，过滤文件)

3.3.3 字体对话框  QFontDialog：：getFont 
```



## 4 界面布局

4.1 实现登陆窗口

4.2 利用布局方式 给窗口进行美化

4.3 选取 widget  进行布局 ，水平布局、垂直布局、栅格布局

4.4 给用户名、密码、登陆、退出按钮进行布局

4.5 默认窗口和控件之间 有9间隙，可以调整 layoutLeftMargin

4.6 利用弹簧进行布局

## 5 控件

```
5.1 按钮组

5.1.1 QPushButton  常用按钮 

5.1.2 QToolButton  工具按钮  用于显示图片，如图想显示文字，修改风格：toolButtonStyle ， 凸起风格autoRaise

5.1.3 radioButton  单选按钮，设置默认 ui->rBtnMan->setChecked(true); 

5.1.4 checkbox多选按钮，监听状态，2 选中  1 半选 0 未选中

5.2 QListWidget 列表容器

5.2.1 QListWidgetItem * item 一行内容 

5.2.2 ui->listWidget ->addItem ( item )

5.2.3 设置居中方式item->setTextAlignment(Qt::AlignHCenter);

5.2.4 可以利用addItems一次性添加整个诗内容

5.3 QTreeWidget 树控件

5.3.1 设置头  

5.3.1.1 ui->treeWidget->setHeaderLabels(QStringList()<< "英雄"<< "英雄介绍");

5.3.2 创建根节点

5.3.2.1 QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList()<< "力量");

5.3.3 添加根节点 到 树控件上

5.3.3.1 ui->treeWidget->addTopLevelItem(liItem);

5.3.4 添加子节点

5.3.4.1 liItem->addChild(l1);

5.4 QTableWidget 表格控件

5.4.1 设置列数 

5.4.1.1 ui->tableWidget->setColumnCount(3);

5.4.2 设置水平表头

5.4.2.1 ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<< "性别"<< "年龄");

5.4.3 设置行数 

5.4.3.1 ui->tableWidget->setRowCount(5);

5.4.4 设置正文

5.4.4.1 ui->tableWidget->setItem(0,0, new QTableWidgetItem("亚瑟"));

5.5 其他控件介绍

5.5.1 stackedWidget  栈控件

5.5.1.1 ui->stackedWidget->setCurrentIndex(1);

5.5.2 下拉框

5.5.2.1 ui->comboBox->addItem("奔驰");

5.5.3 QLabel 显示图片

5.5.3.1 ui->lbl_Image->setPixmap(QPixmap(":/Image/butterfly.png"))

5.5.4 QLabel显示动图  gif图片

5.5.4.1 ui->lbl_movie->setMovie(movie);

5.5.4.2 movie->start();
```

