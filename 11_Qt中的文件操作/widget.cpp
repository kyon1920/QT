#include "widget.h"
#include "ui_widget.h"
#include <QFile>    // 文件操作
#include <QFileDialog>    // 文件对话框
#include <QDebug>
#include <QDateTime>    // 时间
#include <QDataStream>    // 数据流，以二进制方式操作文件(音频、图片)
#include <QTextStream>    // 以文本方式操作文件，读写的时候可以指定编码
#include <QBuffer>    // 内存文件读写

// 很实用的一个技巧
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();
    readData();
    writeTextData();
    readTextData();

    // 内存文件操作
    QBuffer memFile;    // 创建内存文件
    memFile.open(QIODevice::WriteOnly);

    // 也可以在创建对象的时候就绑定缓冲区(字节数组)
    // 写的内容就放进字节数组中去了
    // QByteArray array;
    // QBuffer memFile(&array);

    // 指定设备
    // QDataStream stream(&memFile);
    // stream << QString("测试") << 250;
    // memFile.close();
    // 取的时候也需要借助QDataStream

    // 写到缓冲区
    memFile.write("012012012");
    memFile.write("234234234234");
    cout << "memFile = " << memFile.buffer();    // 取出缓存区的字符
    memFile.close();




}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_buttonRead_pressed(){}
void Widget::on_buttonRead_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../","TEXT(*.txt)");
    if (path.isEmpty() == false)
    {
        // 文件对象
        QFile file(path);
        // 打开文件，只读方式
        bool isOk = file.open(QIODevice::ReadOnly);
        if (isOk == true)
        {
            #if 0
            // 读文件，默认只识别 UTF-8 编码
            QByteArray array = file.readAll();
            // 显示到编辑区
            // ui -> textEdit -> setText(QString(array));
            // 可以不用转换，会自动转换
            ui -> textEdit -> setText(array);
            #endif

            // 一行一行读
            QByteArray array;
            while (file.atEnd() == false)
            {
                // 读一行
                array += file.readLine();
            }
            ui -> textEdit -> setText(array);
        }
        // 关闭文件
        file.close();

        // 获取文件信息
        QFileInfo info(path);
        qDebug() << "文件名字：" << info.fileName();    // 如果有中文，就转换一下 + .toUtf8().data();
        qDebug() << "文件后缀：" << info.suffix();
        qDebug() << "文件大小：" << info.size();    // 以字节为单位，K/1024  M/1024/1024
        qDebug() << "文件创建时间：" << info.created().toString("yyyy-MM-dd hh:mm:ss");    // 格式 2019-08-03 15:13:00
    }
}

void Widget::on_buttonWrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if (path.isEmpty() == false)
    {
        // 创建文件对象
        QFile file;
        // 关联文件名字
        file.setFileName(path);
        // 打开文件，只写模式
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk == true)
        {
            // 获取编辑区内容
            QString str = ui -> textEdit -> toPlainText();
            // 写文件
            // 把QString转换成QByteArray
            //file.write(str.toUtf8());

            // 或者
            // QString -> C++ string -> char*
            file.write(str.toStdString().data());

            // QString -> QByteArray
            QString buf = "123";
            QByteArray a = buf.toUtf8();    // 存在中文的转换
            a = buf.toLocal8Bit();    // 转换成本地编码
            // QByteArray -> char*
            char* b = a.data();
            // char * -> QString
            char *p = "abc";
            QString c = QString(p);
        }
        file.close();
    }
}

// QdataStream操作
void Widget::writeData()
{
    // 创建文件对象
    QFile file("../QTtest.txt");
    // 打开文件
    bool isOk = file.open(QIODevice::WriteOnly);
    if (true == isOk)
    {
        // 创建数据流，和file文件关联
        // 往数据流中输入数据，相当于往文件里写数据
        QDataStream stream(&file);
        stream << QString("主要看气质 ") << 250;
    }
    file.close();
}

void Widget::readData()
{
    QFile file("../QTtest.txt");
    bool isOk = file.open(QIODevice::ReadOnly);
    if (true == isOk)
    {
        // 往数据流中读数据，相当于在文件里读数据
        QDataStream stream(&file);
        // 读的时候，按写的顺序取数据
        QString str;
        int a;
        stream >> str >> a;
        qDebug() << "str = " << str.toUtf8().data();
        qDebug() << "a = " << a;
        cout << "str = " << str.toUtf8().data();
        cout << "a = " << a;
    }
    file.close();
}

// 以文本方式读写文件
void Widget::writeTextData()
{
    QFile file;
    file.setFileName("../demo.txt");
    bool isOk = file.open(QIODevice::WriteOnly);
    if (isOk == true)
    {
        QTextStream stream(&file);
        // 指定编码
        stream.setCodec("UTF-8");
        stream << QString("主要看气质") << 250;
    }
    file.close();

}

// 不推荐下面第一种这样读，还是要一行一行读
void Widget::readTextData()
{
    QFile file("../demo.txt");
    bool isOk = file.open(QIODevice::ReadOnly);
    if (true == isOk)
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        // 第一种
        QString str;
        int a;
        stream >> str >> a;
        cout << "str = " << str;
        cout << "a = " << a;

        //第二种
        QString str1 = stream.readAll();
        cout << "str1 = " << str;

        // 一行一行读
        while(file.atEnd() == false)
        {
            QString str2 = stream.readLine();
            cout << "str2 = " << str2;
        }

    }
    file.close();
}
