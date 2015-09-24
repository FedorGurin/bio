#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include <math.h>
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
//! преобразование нуклеотида в целое число
int convertNuk(QChar ch)
{
    if(ch == QChar('A'))
        return 0;
    else if(ch == QChar('T'))
        return 3;
    else if(ch == QChar('C'))
        return 1;
    else if(ch == QChar('G'))
       return 2;

    qDebug("bad\n");
    return -1;
}
//! преобразование шаблона в число
int patternToNumber(QString pattern)
{
    int result=0;
    int size=pattern.length();
    for(int i=0;i<size;i++)
    {
        result+=convertNuk(pattern[size-i-1])*powf(4,i);
    }
    return result;
}

int* computFreq(QString dna,int k)
{
    int size=powf(4,k);
    int *mas=new int[size];
    int j;
    for(int i=0;i<size;i++)
        mas[i]=0;
    for(int i=0;i<(dna.length() - k);i++)
    {
        QString pattern=dna.mid(i,k);
        j=patternToNumber(pattern);
        mas[j]=mas[j]+1;
    }
    return mas;
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

    QFile file("./dataset.txt");
    QFile fileRes("./result.txt");
    bool isOpen=file.open(QIODevice::ReadOnly);
    bool isOpenRes=fileRes.open(QIODevice::WriteOnly);
    if(isOpen == false)
        qDebug()<<"Not open";
    QTextStream in(&file);
    QTextStream out(&fileRes);

    QString str=in.readAll();


    int *ptr=computFreq(str,2);
  //  QString pattern("CTTGATCAT");
  //  QString res=patternMatch(str,pattern);
//    QString reverse=reverseDNA(str);

    int size=powf(4,2);
    qDebug("vslue=%d\n",size);
    for(int i=0;i<size;i++)
        out<<QString::number(ptr[i])<<" ";
        out.flush();
qDebug("ready\n");

    //QString list=frequentWords(str,12);
    //qDebug("String=%s\n",qPrintable(reverse));
    //int res=patternCount(str,"GTATACCGT");
    //qDebug("Count = %d\n",res);
    return a.exec();
}
