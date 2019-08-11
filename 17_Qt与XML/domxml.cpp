#include "domxml.h"

DomXML::DomXML()
{

}

// 创建xml文件
void DomXML::createXMLfile(QString filepath)
{
    QFile file(filepath);    // 关联文件名字
    if (true == file.exists())
    {
        qDebug() << "文件已经存在！";
        return;
    }
    else
    {
        // 不存在才创建
        // 以只写方式打卡
        bool isOk = file.open(QIODevice::WriteOnly);
        if (true == isOk)    // 如果打卡成功
        {
            // 创建xml文档对象
            QDomDocument doc;
            // 创建xml头部格式 <xml version='1.0' encoding='UTF-8'?>
            QDomProcessingInstruction ins;
            ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'UTF-8\'");

            // 根节点元素
            QDomElement root = doc.createElement("student");
            doc.appendChild(root);

            // 保存
            QTextStream stream(&file);    // 文本流关联文件
            doc.save(stream,4);    // 4 代表缩进字符
            file.close();
        }
        else
        {
            qDebug() << "WriteOnly Error!";
            return;
        }
    }
}

void DomXML::appendXML(QString filepath, QStringList list)
{
    // 以只写方式打开文件
    QFile file(filepath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (true == isOk)
    {
        // file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);
        if (isOk)
        {
            file.close();    // 关闭文件
            // 获取根节点元素
            QDomElement root = doc.documentElement();

            QDateTime date = QDateTime::currentDateTime();    // 获取当前时间
            QString dateStr = date.toString("yyyy-MM-dd");

            // 判断根节点上面有没有子节点
            if (root.hasChildNodes())    // 如果有字节的
            {
                // 查找最后一个子节点
                QDomElement lastEmt = root.lastChildElement();
                if (lastEmt.attribute("date") == dateStr)
                // 有当天日期
                {
                    writeXML(doc, lastEmt, list);
                }
                // 如果没有
                else
                {
                    // 创建子节点:日期
                    QDomElement dateEmt = doc.createElement("日期");
                    // 创建date属性
                    QDomAttr dateAttr = doc.createAttribute("date");
                    // 设定属性的值
                    dateAttr.setNodeValue(dateStr);
                    // 节点和属性关联
                    dateEmt.setAttributeNode(dateAttr);
                    // 把新建节点追加到根节点
                    root.appendChild(dateEmt);

                    DomXML::writeXML(doc, root, list);
                }
            }
            else    // 没有子节点
            {
                // 创建子节点:日期
                QDomElement dateEmt = doc.createElement("日期");
                // 创建date属性
                QDomAttr dateAttr = doc.createAttribute("date");
                // 设定属性的值
                dateAttr.setNodeValue(dateStr);
                // 节点和属性关联
                dateEmt.setAttributeNode(dateAttr);
                // 把新建节点追加到根节点
                root.appendChild(dateEmt);

                DomXML::writeXML(doc, dateEmt, list);
            }
            // 保存文件
            isOk = file.open(QIODevice::WriteOnly);
            if (isOk)
            {
                QTextStream stream(&file);
                doc.save(stream,4);
                file.close();
            }
        }
        else
        {
            qDebug() << "setContent Error!";
            return;
        }
    }
    else
    {
        qDebug() << "ReadOnly Error!";
    }
}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    // 当前时间获取
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("hh-mm-ss");

    // 创建时间节点元素
    QDomElement timeEmt = doc.createElement("时间");
    // 创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    // 给属性设置值
    timeAttr.setNodeValue(timeStr);
    // 时间节点元素和属性进行关联
    timeEmt.setAttributeNode(timeAttr);
    // 把时间节点加到日期节点后面
    root.appendChild(timeEmt);

    // 创建姓名节点元素
    QDomElement name = doc.createElement("姓名");
    // 创建属性
    QDomAttr nameAttr = doc.createAttribute("Name");
    // 给属性设置值
    nameAttr.setNodeValue(list.at(0));
    // 姓名节点元素和属性进行关联
    name.setAttributeNode(nameAttr);
    // 把姓名节点加到日时间节点后面
    timeEmt.appendChild(name);

    // 创建性别节点元素
    QDomElement sex = doc.createElement("性别");
    // 创建属性
    QDomAttr sexAttr = doc.createAttribute("Sex");
    // 给属性设置值
    sexAttr.setNodeValue(list.at(1));
    // 性别节点元素和属性进行关联
    sex.setAttributeNode(sexAttr);
    // 把性别节点加到时间节点后面
    timeEmt.appendChild(sex);

    // 创建年龄节点元素
    QDomElement age = doc.createElement("年龄");
    // 创建属性
    QDomAttr ageAttr = doc.createAttribute("Age");
    // 给属性设置值
    ageAttr.setNodeValue(list.at(2));
    // 年龄节点元素和属性进行关联
    age.setAttributeNode(ageAttr);
    // 把年龄节点加到时间节点后面
    timeEmt.appendChild(age);

    // 创建简介节点元素
    QDomElement jianjie = doc.createElement("简介");
    // 设置内容
    QDomText text = doc.createTextNode(list.at(3));
    jianjie.appendChild(text);
    // 把年龄节点加到时间节点后面
    timeEmt.appendChild(jianjie);
}

void DomXML::readXML(QString filepath, QStringList &NList, QStringList &SList, QStringList &AList, QStringList &JList)
{
    // 以只写方式打开文件
    QFile file(filepath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (true == isOk)
    {
        // file和xml文档对象关联
        QDomDocument doc;
        isOk = doc.setContent(&file);
        file.close();

        QDateTime date = QDateTime::currentDateTime();
        QString dateStr = date.toString("yyyy-MM-dd");
        if (isOk)    // 如果关联成功
        {
            // 获取根节点
            QDomElement root = doc.documentElement();

            if(root.hasChildNodes())    // 有无子节点
            {
                 // 找最后一个节点元素
                QDomElement lastEmt = root.lastChildElement();
                if (lastEmt.attribute("date") == dateStr)    // 判断有没有当前日期
                {
                    // 找出当前日期下所有时间子节点
                    QDomNodeList listall =  lastEmt.childNodes();
                    for (int i = 0; i < listall.size(); ++i)
                    {
                        // list.at(0).toElement();
                        // 转换为元素，找到时间节点下的所有子节点
                        QDomNodeList subList = listall.at(i).toElement().childNodes();
                        // Name
                        QString name = subList.at(0).toElement().text();
                        NList.append(name);

                        QString sex = subList.at(1).toElement().text();
                        SList.append(sex);

                        QString age = subList.at(2).toElement().text();
                        AList.append(age);

                        QString jianjie = subList.at(3).toElement().text();
                        JList.append(jianjie);
                    }
                }
                else
                {
                    qDebug() << lastEmt.attribute("date") << "没有当天日期!";
                    return;
                }
            }
        }
        else
        {
            qDebug() << "setContent Error!";
            return;
        }
    }
    else
    {
        qDebug() << "ReadOnly Error!";
        return;
    }
}
