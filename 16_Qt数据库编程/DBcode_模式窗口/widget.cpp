#include "widget.h"
#include "ui_widget.h"
#include <QSqlRecord>    // 记录类

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
    db.setDatabaseName("student");    // 用哪一个数据库
    // 打开数据库
    if (!db.open())
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }

    // 设置模型
    model = new QSqlTableModel(this);
    model -> setTable("student");    // 指定使用na哪一个表

    // 把model放在view
    ui -> tableView -> setModel(model);
    // 显示model里面的数据
    model -> select();

    // 改变元素属性名
    model ->setHeaderData(0, Qt::Horizontal, "名字");
    // 点击确定之后才生效，设置Model编辑模式，手动提交修改
    model -> setEditStrategy(QSqlTableModel::OnManualSubmit);

    // ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);    // 只读，不允许修改

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonAdd_clicked()
{
    // 添加空记录
    QSqlRecord record = model -> record();    // 获取空记录
    // 获取行号
    int row = model->rowCount();
    model -> insertRecord(row, record);    // 插入空记录

}

void Widget::on_buttonSure_clicked()
{
    model -> submitAll();    // 提交动作
}

void Widget::on_buttonCancel_clicked()
{
    model -> revertAll();     // 取消所有动作
    model -> submitAll();    // 提交所有动作
}

void Widget::on_buttonDel_clicked()
{
    // 多选删除可以实现一下删除多行
    // 需要先取出索引
    // 取出索引所对应行号

    // 获取选中的模型
    QItemSelectionModel *sModel = ui -> tableView -> selectionModel();
    // 取出模型中的索引
    QModelIndexList list = sModel -> selectedRows();
    // 删除所有选中行
    for (int i = 0; i < list.size(); ++i)
    {
        model -> removeRow(list.at(i).row());
    }
}
void Widget::on_buttonFind_clicked()
{
    QString name = ui -> lineEdit -> text();
    // 组包，注意单引号
    QString str = QString("name = '%1'").arg(name);

    model -> setFilter(str);
    model -> select();
}
