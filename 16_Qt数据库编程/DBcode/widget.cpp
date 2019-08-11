#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>    // 数据库头文件
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>    // 对SQL语句进行操作的类
#include <QVariantList>    // 泛型

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // 连接数据库
    db.setHostName("localhost");    // 数据库服务器IP
    db.setUserName("root");    // 数据库用户名
    db.setPassword("mysql");    // 数据库密码
    db.setDatabaseName("info");    // 用哪一个数据库
    // 打开数据库
    if (!db.open())
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }

    QSqlQuery query(db);    // 如果只操作一个数据库，参数可为空 QSqlQuery query;
    // 直接放数据库操作语句
    // query.exec("这里为数据库操作语句");

    // 批量插入
    // odbc 风格
    /*  // 预处理语句 ? 相当于占位符
    query.prepare("insert into info(name, age) value(?, ?)");
    // 给字段设置内容 list
    QVariantList nameList;
    nameList << "zhang" << "wang" << "zhao";
    QVariantList ageList;
    ageList << 10 << 22 << 18;
    // 给字段绑定相应的值，按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    // 执行预处理命令
    query.execBatch();*/

    // oracle 风格
    // 占位符改为： ": + 自定义名字"
    query.prepare("insert into info(name, age) value(:name, :age)");
    // 给字段设置内容 list
    QVariantList nameList;
    nameList << "zhang" << "wang" << "zhao";
    QVariantList ageList;
    ageList << 10 << 22 << 18;
    // 给字段绑定相应的值，按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    // 给字段绑定，不局限于顺序
    query.bindValue(":age", ageList);
    query.bindValue(":name", nameList);
    // 执行预处理命令
    query.execBatch();

    // 查询
    query.exec("selete * from info");
    // 从0行开始不包括字段，存入一个链表中
    while (query.next())
    {
        // 取出当前行的内容
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString()
                 << query.value("age").toInt();
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonDel_clicked()
{
    // 获取行编辑内容
    QString name = ui -> lineEdit -> text();
    // 开启一个事务
    QSqlDatabase::database().transaction();

    QString sql = QString("delete from info where name = '%1'").arg(name);
    QSqlQuery query;
    query.exec(sql);
}

void Widget::on_buttonSure_clicked()
{
    // 确定删除
    QSqlDatabase::database().commit();
}

void Widget::on_buttonCancel_clicked()
{
    // 回滚，撤销
    QSqlDatabase::database().rollback();
}
