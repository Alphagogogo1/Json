#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QBitArray>
#include <QDebug>
void readJsonFromFile(QString &fileName)
{
    /*构造File类*/
    /*设置要读的文件*/
    QFile file(fileName);
    /*打开文件*/
    file.open(QIODevice::ReadOnly);
    /*读文件*/
    QByteArray byteArray=file.readAll();
    /*关闭文件*/
    file.close();

    /*将QByteArray类对象转换为QJsonDocument*/
    QJsonDocument jsonDoc=QJsonDocument::fromJson(byteArray);

    /*判断是数组还是对象*/
    if(jsonDoc.isObject())
    {
        /*获取对象*/
        QJsonObject jsonObject=jsonDoc.object();
        /*获取对象中所有的key值*/
        QStringList keys=jsonObject.keys();
        for(auto i:keys)
        {
            /*获取key值*/
            QString key=i;
            /*根据key值*/
            QJsonValue jsonValue=jsonObject.value(key);
            /*判断value的值*/
            if(jsonValue.isString())
            {
                qDebug()<<key<<":"<<jsonValue.toString();
            }
            else if(jsonValue.isDouble())
            {
                qDebug()<<key<<":"<<jsonValue.toDouble();
            }
            else if(jsonValue.isBool())
            {
                qDebug()<<key<<":"<<jsonValue.toBool();
            }
            else if(jsonValue.isObject())
            {
                QJsonObject obj=jsonValue.toObject();
                QStringList subKeys=obj.keys();

                qDebug()<<key<<":{";
                for(auto i:subKeys){
                    QJsonValue subJsonValue=obj.value(i);
                    qDebug()<<" "<<subJsonValue.toString();
                }
                qDebug()<<"}";
            }
            else if(jsonValue.isArray())
            {
                qDebug()<<key<<":[";
                QJsonArray arr=jsonValue.toArray();
                for(auto i:arr)
                {
                    if(i.isString())
                        qDebug()<<" "<<i.toString();
                }
                qDebug()<<"]";
            }
        }
    }
    else if(jsonDoc.isArray())
    {
        /*获取QJsonArray对象*/
        QJsonArray array=jsonDoc.array();
        qDebug()<<"[";
        for(auto i:array)
        {
            QJsonValue value=i;
            if(value.isString())
            {
                qDebug()<<value.toString();
            }
            else if(value.isDouble())
            {
                qDebug()<<value.toDouble();
            }
            else if(value.isBool())
            {
                qDebug()<<value.toBool();
            }
            else if(value.isArray())
            {
                qDebug()<<"[";
                QJsonArray subArray=value.toArray();
                for(auto i:subArray)
                {
                    qDebug()<<" "<<i.toString();
                }
                qDebug()<<"]";
            }
            else if(value.isObject())
            {
                qDebug()<<"{";
                QJsonObject subObject=value.toObject();
                QStringList subKeys=subObject.keys();
                for(auto i:subKeys)
                {
                    QJsonValue value=subObject[i];
                    if(value.isString())
                    {
                        qDebug()<<" "<<i<<":"<<value.toString();
                    }
                }
                qDebug()<<"}";
            }
        }
        qDebug()<<"]";
    }
    else if(jsonDoc.isEmpty())
    {
        return;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName="test.json";
    readJsonFromFile(fileName);
    return a.exec();
}
