#include "mainwidget.h"
#include <QSizePolicy>
#include <QDebug>    //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this -> setWindowTitle("老张");
    b1.setParent(this);
    b1.setText("close");
    b1.move(50,50);

    //使用标准信号和槽
    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);
    /* &b1  信号发出者，指针类型
     * &QPushButton::pressed  处理的信号(按下)  &发送者的类名::信号名字
     * this  信号接收者
     * &MainWidget::close  槽函数，信号处理函数  &接收者的类名::槽函数形式
     */

    b2 = new QPushButton;
    b2->setParent(this);
    b2->setText("^_^");
    b2->move(0,0);

    //使用自定义信号和槽
    /* 自定义槽，就是普通函数，和普通函数用法相同
     * Qt5：任意的成员函数、普通全局函数、静态函数
     * 槽函数需要和信号一致(参数)
     * 由于信号都是没有返回值的，所以槽函数一定没有返回值
     */
    b3.setParent(this);
    b3.setText("看我变变变");
    b3.move(100,100);
    connect(&b3, &QPushButton::released, this, &MainWidget::changeTextSlot);

    b4 = new QPushButton;
    b4 -> setParent(this);
    b4 -> setText("切换到老王的窗口");
    b4 -> move(150,150);
    b4 -> setFixedSize(183,25);
    connect(b4, &QPushButton::released, this, &MainWidget::changeWindowSlot);

    //当前窗口处理子窗口的信号
    void (SubWidget::*ReplaceSlot1)() = &SubWidget::changeWindowSlot;

    void (SubWidget::*ReplaceSlot2)(int, QString) = &SubWidget::changeWindowSlot;

    connect(&w, ReplaceSlot1, this, &MainWidget::changeWindowsSlot);

    connect(&w, ReplaceSlot2, this, &MainWidget::dealWindowSlot);

    //Qt4信号连接
    //Qt4槽函数必须有public slots关键字来修饰
    //connect(&w, SIGNAL(函数可选，不用函数指针转换), this,SLOT(槽处理函数))
    //connect(&w, SIGNAL(changeWindowSlot()),this, SLOT(changeWindowsSlot));
    //connect(&w, SIGNAL(changeWindowSlot(int, QString)), this, SLOT(dealWindowSlot));
    //不推荐
    //理由：SIGNAL、SLOT 会将函数名字转换成字符串，不进行错误检测

    //显示子窗口
    //w.show();

    //设置窗口大小
    //resize(400,300);

    //Lambda表达式，匿名函数对象
    //C++11增加的新特性
    //配合Qt信号一起使用，非常方便
    //使用需要在项目文件加： CONFIG += C++11
    //以后能用这种方式就尽量用这种方式connect
    QPushButton *b6 = new QPushButton;
    b6 -> setParent(this);
    b6 -> setText("Lambda表达式");
    b6 -> move(250,250);
    connect(b6, &QPushButton::released,
            [=]()
            // [] 内写任变量或者类成员 传递相对应的变量和类成员
            // = ：把外部所有局部变量、类中所有成员以值传递进函数，不能在函数体内改变
            // 若想要在函数体内改变变量的值，需要这样定义 [变量或者类对象列表]() mutable {函数体}
            // this：类中所有成员传递
            // &：把外部所有局部变量以引用的方式传递，不包括类中成员，下面一定不能用这种方法
            {
               b6 -> setText("=");
                qDebug() << "Lambda表达式";
            }
            );
}

void MainWidget::changeTextSlot()
{
    b3.setFixedSize(180,25);
    b3.setText("看到了吗？我变了！");
}
void MainWidget::changeWindowSlot()
{
    //显示子窗口
    w.show();
    //隐藏本窗口
    this -> hide();
}
void MainWidget::changeWindowsSlot()
{
    //隐藏子窗口
    w.hide();
    //显示本窗口
    this -> show();
}
void MainWidget::dealWindowSlot(int a, QString str)
{
    qDebug() << a << str;
    //如果发现输出的不是汉字，而是编码，需要转换
    //toUtf8()转换称为QByteArray类型，不认识，在通过data()方法转换为char*
    //qDebug() << a << str.toUtf8().data();
}

MainWidget::~MainWidget()
{
    delete b2;
    delete b4;
}
