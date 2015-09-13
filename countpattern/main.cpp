#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
int patternCount(QString str,QString pattern)
{
    int i=0;
    int count=0;
    for(i=0;i<(str.length() - pattern.length());i++)
    {
        if(str.mid(i,pattern.length()) == pattern)
        {
            count++;
        }
    }
    return count;
}
QString patternMatch(QString dna, QString pattern)
{
    QString result="";
    //count=new long[dna.length()- pattern.length()];
    for(int i=0;i<(dna.length() - pattern.length());i++)
    {
      //  count[i]=0;
        if(dna.mid(i,pattern.length()) == pattern)
            result.append(QString::number(i) + " ");
    }
    return result;
}

QString frequentWords(QString dna, int len_pattern)
{
    QString result;
    long *count=new long[dna.length()- len_pattern];
    //long count[40];//=new long[dna.length()- len_pattern];
    long maxCount=0;
    for(int i=0;i<(dna.length() - len_pattern);i++)
    {
        count[i]=0;
        QString pattern=dna.mid(i,len_pattern);
        count[i]=patternCount(dna.mid(i),pattern);
        if(count[i]>maxCount)
            maxCount=count[i];
    }
    for(int i=0;i<(dna.length() - len_pattern);i++)
    {
        if(count[i] == maxCount)
            result.append(dna.mid(i,len_pattern)+" ");
    }
    return result;
}
QString reverseDNA(QString dna)
{
    QString result;
    for(int i=dna.length()-1;i>=0;i--)
    {
        if(dna[i] == 'A')
            result.append('T');
        else if(dna[i] == 'T')
            result.append('A');
        else if(dna[i] == 'C')
            result.append('G');
        else if(dna[i] == 'G')
            result.append('C');
    }
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("./Vibrio_cholerae.txt");
    QFile fileRes("./result.txt");
    bool isOpen=file.open(QIODevice::ReadOnly);
    bool isOpenRes=fileRes.open(QIODevice::WriteOnly);
    if(isOpen == false)
        qDebug()<<"Not open";
    QTextStream in(&file);
    QTextStream out(&fileRes);

    QString str=in.readAll();


    QString pattern("CTTGATCAT");
    QString res=patternMatch(str,pattern);
//    QString reverse=reverseDNA(str);

        out<<res;
        out.flush();
qDebug("ready\n");

    //QString list=frequentWords(str,12);
    //qDebug("String=%s\n",qPrintable(reverse));
    //int res=patternCount(str,"GTATACCGT");
    //qDebug("Count = %d\n",res);
    return a.exec();
}
