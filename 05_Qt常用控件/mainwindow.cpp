#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCompleter>    // 实现下面的输入提示头文件
#include <QStringList>    // 字符串列表
#include <QLabel>
#include <QMovie>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取lineEdit的内容
    QString str = ui -> lineEdit -> text();
    qDebug() << str;

    // 设置内容
   // ui -> lineEdit -> setText("hahaha");

    // 设置内容显示间距
    ui -> lineEdit -> setTextMargins(25,0,0,0);

    // 设置内容显示方式：密码模式
    // ui -> lineEdit -> setEchoMode(QLineEdit::Password);

    // 有提示的方式输入
    QStringList list;
    list << "hello," << "how are you" << "hehe";
    QCompleter *com = new QCompleter(list, this);
    com -> setCaseSensitivity(Qt::CaseInsensitive);
    ui -> lineEdit -> setCompleter(com);

    str = ui -> lineEdit -> text();
    qDebug() << "您输入的字符串为：" + str;

    // 设置文本内容
    ui -> labelText -> setText("^_^");

    // 设置图片
    ui -> labelImage -> setPixmap(QPixmap("://1.jpg"));
    // 设置图片自适应
    ui -> labelImage -> setScaledContents(true);

    // 创建动画
    QMovie *myMovie = new QMovie("://C:/Users/小王子/Pictures/U.gif");
    // 设置动画
    ui -> labelGif -> setMovie(myMovie);
    // 启动动画
    myMovie -> start();
    ui -> labelGif -> setScaledContents(true);

    // 设置html
    ui -> labelUrl -> setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>>");
    // 打开外部链接
    ui -> labelUrl -> setOpenExternalLinks(true);

    // 数码管
    ui -> lcdNumber -> display("ABC123");

    // 进度条
    ui -> progressBar -> setMinimum(0);
    ui -> progressBar -> setMaximum(200);
    ui -> progressBar -> setValue(150);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_change_clicked()
{

    // 跳转页面
    //static int i = 0;
    //ui -> stackedWidget ->setCurrentIndex( ++i % 4);
}
