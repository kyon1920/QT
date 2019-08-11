#include "mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>    // 标签，显示文字用的
#include <QTextEdit>    // 文本编辑区头文件
#include <QDockWidget>    // 浮动窗口头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 菜单栏
    // 工具栏
    // 核心控件
    // 浮动窗口
    this -> setMinimumSize(500,500);
    this -> setMaximumSize(500,500);

    // 菜单栏
    QMenuBar *menubar = menuBar();
    // 添加菜单
    QMenu *menu = menubar -> addMenu("文件");
    // 添加菜单项，添加动作
    QAction *newMenu0 =  menu -> addAction("新建");

    connect(newMenu0, &QAction::triggered,
            [=]()
            {
                qDebug() << "新建被按下！";
            }
            );

    QAction *newMenu1 =  menu -> addAction("编辑");
    connect(newMenu1, &QAction::triggered,
            [=]()
            {
                qDebug() << "编辑被按下！";
            }
            );
    // 添加一个分割线
    menu -> addSeparator();

    QAction *newMenu2 =  menu -> addAction("关闭");
    connect(newMenu2, &QAction::triggered,
            [=]()
            {
                menu -> close();
            }
            );

    // 工具栏：菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    // 工具栏 添加快捷键
    toolBar -> addAction(newMenu0);
    QPushButton *b = new QPushButton(this);
    b -> setText("^_^");
    //添加小控件
    toolBar -> addWidget(b);
    connect(b, &QPushButton::clicked,
            [=]()
            {
                b -> setText("~_~");
            }
            );

    // 状态栏
    QStatusBar *staBar = statusBar();
    QLabel *label = new QLabel(this);
    label -> setText("Normal text file");
    staBar -> addWidget(label);
    // addWidget() 从左往右添加
    staBar -> addWidget(new QLabel("2",this));
    // addPermanentWidget() 从右往左依次添加
    staBar -> addPermanentWidget(new QLabel("Hello world!",this));

    // 核心控件
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    // 浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //给浮动窗口添加控件
    QTextEdit *textEdit1 = new QTextEdit(this);
    dock -> setWidget(textEdit1);
}

MainWindow::~MainWindow()
{

}
