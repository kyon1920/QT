#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 添加背景色
    ui -> label_2 -> setStyleSheet("QLabel{color:rgb(255,0,0)}");
    ui -> label_3 -> setStyleSheet("QLabel{color:rgb(255,0,0)}");

    //ui -> pushButton -> setStyleSheet("QPushButton{color:rgb(0,255,0)}");
    //ui -> pushButton_2 -> setStyleSheet("QPushButton{background-color:rgb(255,0,0)}");

    // 添加背景图
    //this -> setStyleSheet("QPushButton{border-width:15px;border-image:url(://557.jpg); 10 10 10 10 stretch stretch");

    // 处理伪状态
    // 设置边距颜色
    ui -> pushButton -> setStyleSheet("QPushButton{border:20px outset green};QPushButton{border-image:url(://557.jpg)}"
                                      "QPushButton:hover{border-image:url(://557.jpg)}");
    // 放上去显示图片
    ui -> pushButton_2 -> setStyleSheet("QPushButton:hover{border-image:url(://557.jpg)}");
    // 点击显示图片
    ui -> pushButton_2 -> setStyleSheet("QPushButton:pressed{border-image:url(://557.jpg)}");

}

MainWindow::~MainWindow()
{
    delete ui;
}
