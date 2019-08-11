#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>    // 对话框
#include <QDebug>
#include <QMessageBox>    // 标准对话框
#include <QFileDialog>    // 文件对话框


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Dialog");
    this -> resize(500,500);

    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar -> addMenu("对话框");

    // 创建模态对话框
    QAction *p1 = menu -> addAction("模态对话框");
    connect(p1, &QAction::triggered,
            []()
            {
                QDialog dlg;
                dlg.resize(300, 300);
                dlg.setWindowTitle("模态对话框");
                dlg.exec();
                qDebug() << "正在执行！";
             }
            );

    // 创建非模态对话框
    // 如果在下面lambda表达式中定义非模态对话框，我们将看不见此对话框
    // 因为它这里没有像模态对话框的exec()方法，而是调用show()方法来显示对话框
    // 在一次执行完了就完了
    // 所以得把它的定义放在类中，而不能放在构造函数中

    // 如果真想要放在构造函数中，就得利用申请空间的方法定义
    // Qdialog *p = new QDialog(this);
    // p -> show()
    // 这样它也不会释放，知道程序运行完成才释放  这种方法不好，只有在主程序结束时才释放
    // Qdialog *p = new QDialog(this);
    // p -> setAttribute(Qt::WA DeleteOnClose);
    // p -> show()
    // 加上上面那条语句才完美，关闭即释放
    QAction *p2 = menu -> addAction("非模态对话框");
    connect(p2, &QAction::triggered,
            [=]()
            {
                dlg.resize(300, 300);
                dlg.setWindowTitle("非模态对话框");
                dlg.show();
                qDebug() << "正在执行！";
             }
            );
    // 标准对话框
    QAction *p3 = menu -> addAction("关于对话框");
    connect(p3, &QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"about","关于Qt");
             }
            );
    QAction *p4 = menu -> addAction("问题对话框");
    connect(p4, &QAction::triggered,
            [=]()
            {
                int ret = QMessageBox::question(this,"question","Are you OK?", QMessageBox::Ok | QMessageBox::Cancel);
                switch (ret) {
                case QMessageBox::Yes | QMessageBox::Ok:
                    qDebug() << "I am OK!";
                    break;
                case QMessageBox::No | QMessageBox::Cancel:
                    qDebug() << "I am Bad!";
                    break;
                default:
                    break;

                }
            }
            );
    // 文件对话框
    QAction *p5 = menu -> addAction("文件对话框");
    connect(p5, &QAction::triggered,
            [=]()
            {
                QString path = QFileDialog ::getOpenFileName(
                            this,
                            "open",
                            "../",
                            // 指定打开文件格式
                            tr("source (*.cpp *.h);;"
                               "Image(*.png *.xpm *.jpg);;"
                               "Text files (*.txt);;"
                               "XML files (*.xml);;all(*.*)" )
                            );
                qDebug() << path;
             }
            );

}

MainWindow::~MainWindow()
{

}
