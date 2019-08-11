#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();
    // 添加SqlLite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库
    db.setDatabaseName("../test.db");
    // 打开数据库
    if ( !db.open())
    {
        QMessageBox::warning(this, "error", db.lastError().text());
        return;
    }

    QSqlQuery query;
    // 创建数据表
    query.exec("create table student(name varchar(20), age int)");
    // 插入数据
    query.prepare("insert into student(name, age) value('zhang', 20)");
    query.prepare("insert into student(name, age) value(?, ?)");
    // 给字段设置内容 list
    QVariantList nameList;
    nameList << "zhang" << "wang" << "zhao";
    QVariantList ageList;
    ageList << 10 << 22 << 18;
    // 给字段绑定相应的值，按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    // 执行预处理命令
    query.execBatch();
    // 遍历
    query.exec("selete * from student");
    // 从0行开始不包括字段
    while (query.next())
    {
        // 取出当前行的内容
        qDebug() << "SQLite内容：";
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString()
                 << query.value("age").toInt();
    }
}

Widget::~Widget()
{
    delete ui;
}
