#ifndef DOMXML_H
#define DOMXML_H

#include <QString>
#include <QFile>
#include <QDomDocument>    // 文件
#include <QDomProcessingInstruction>    // 格式头部
#include <QDomElement>    // 元素
#include <QTextStream>    // 文件流
#include <QDateTime>    // 日期
#include <QDebug>


class DomXML
{
public:
    DomXML();

    // 创建xml文件
    static void createXMLfile(QString filepath);
    // 为xml文件添加元素
    static void appendXML(QString filepath, QStringList list);

    static void writeXML(QDomDocument &doc, QDomElement &root, QStringList &list);
    static void readXML(QString filepath, QStringList &NList, QStringList &SList, QStringList &AList, QStringList &JList);
};

#endif // DOMXML_H
