#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonSure_clicked();

    void on_buttonCancel_clicked();

    void on_buttonDel_clicked();

    void on_buttonFind_clicked();

private:
    Ui::Widget *ui;

    // 模型
    QSqlTableModel *model;
};

#endif // WIDGET_H
