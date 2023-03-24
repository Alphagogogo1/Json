#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QBitArray>
void writeJsonToFile(QString &fileName)
{
    QJsonArray array;
    /*给array添加对象*/
    array.append("苏X");
    array.append("BU520");
    array.append("125平方");
    array.append(120);
    array.append("车:丰田");
    array.append(true);
    /*添加一个子数组*/
    QJsonArray subArray;
    subArray.append("江苏省");
    subArray.append("南京市");
    subArray.append("建邺区");
    subArray.append("奥体中心");
    array.append(subArray);
    /*添加一个子对象*/
    QJsonObject object;
    object.insert("户主","小明");
    object.insert("wife","小红");
    object.insert("daughter","小小红");
    object.insert("son","小小明");
    array.append(object);

    /*将QJsonObject转换为QJsonDocument*/
    QJsonDocument jsDoc(array);
    /*将QJsonDocument转换为QByteArray*/
    QByteArray byteArray=jsDoc.toJson();
    /*打开文件*/
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    /*写入文件*/
    file.write(byteArray);
    file.close();
    return;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName="test.json";
    writeJsonToFile(fileName);
    return a.exec();
}
