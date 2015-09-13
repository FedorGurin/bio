#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
int patternCount(QString str,QString p)
{
    int i=0;
    int count=0;
    for(i=0;i<(str.length() - p.length());i++)
    {
        if(str.mid(i,p.length()) == p)
        {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("./dataset_2_6.txt");
    bool isOpen=file.open(QIODevice::ReadOnly);
    if(isOpen == false)
        qDebug()<<"Not open";
    QTextStream in(&file);

    QString str=in.readAll();

    int res=patternCount(str,"AGCGGGAAG");
    qDebug("Count = %d\n",res);
    return a.exec();
}
