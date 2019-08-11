# QT

# 关于Qt，你需要知道的这些基础知识

Qt是什么，有什么用？
------
<br>Qt是在1991年由Qt Company开发的`跨平台C++图形用户界面应用程序开发框架`，后来被Nokia收购，然后被Digia收购。它既可以开发`GUI程序`(图形用户界面Graphical User Interface)，也可用于开发`非GUI程序`，比如`控制台工具`和`服务器`。
<br>Qt是一种`面向对象的框架`，使用特殊的代码生成扩展（称为元对象编译器(Meta Object Compiler, moc)）以及一些宏，Qt很容易扩展，并且允许真正地`组件编程`。

Qt能在哪些平台使用?
------
<br>Windows、Linux、iOS、mac OS、Android、QNX、VxWorks ......

Qt是开源的，需要遵循LGPL、GPL协议
------

关于Qt Creator
------
<br>Qt Creator是`跨平台`的 Qt IDE，专门用于Qt框架开发图形界面，Qt Creator 是 Qt 被 Nokia 收购后推出的一款新的轻量级集成开发环境（IDE）。此 IDE 能够跨平台运行，支持的系统包括 Linux（32 位及 64 位）、Mac OS X 以及 Windows。
<br>更多：除了Qt Creator，目前比较流行的是Visual Studio也可以作为Qt开发IDE，简称VS。Qt Creator一安装好就能使用，但是VS是需要自己进行相关设置后才可以使用。

Qt的优势
------

跨平台
---------
<br>能够跨平台运行，实现写一次代码，多平台编译运行。

面向对象：
---------
<br>Qt完美使用了C++语法中`面向对象`的特点，并加以自身的优化，Qt的良好封装机制使得Qt的`模块化程度非常高`，`可重用性较好`，对于用户开发来说是非常方便的。Qt提供了一种称为` signals/slots(信号和槽) `的安全类型来替代 callback，这使得各个元件之间的协同工作变得十分简单。
<br>Qt的核心机制—————信号(signals)-槽(slots) 机制，它是区别于其它GUI工具的最主要特征
<br>信号(signal)：当某个信号所对应的客户或其他所有者的内部状态发生改变时，信号被一个对象发射。只有定义过这个信号的类及其派生类能够发射这个信号。
<br>槽(slot)：被用于接收信号，它们通常是类中的成员函数，一个槽并不知晓是否有一个信号与自己联系，同样，包含有槽函数的对象，也对通信机制一无所知，它们也可以作为一个独立的软件构件。

丰富的API
---------
<br>Qt有很丰富的API(Application Programming Interface,应用程序编程接口)、丰富的C++类，而且提供了基于模板的 date/time、file、collections、I/O device、directory management、serialization类等。

支持2D/3D图像渲染、OpenGL(Open Graphics Library，开放图形库)
---------

拥有大量的开发文档
---------

支持数据库编程和XML
---------
<br>Qt SQL模块使用驱动程序插件操作不同的数据库。支持连接常用的数据库：MySQL、Oracle、SQL Server、SQLite，其中，由于SQLite是轻量级的数据库，所以Qt支持创建生成本地SQLite数据库并管理。
<br>XML是用来`传输和存储数据`的一种`可扩展标记语言`，很类似HTML，XML标签没有被预定义，需要`自行定义标签`，它被设计为具有`自我描述性`，是`W3C的推荐标准`。

<br><br><br>
[我的博客](http://oubc.github.io "无尽光芒")  
