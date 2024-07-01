#include "myqsortm.h"
#include "measured.h"
#include <QVector>
#include <QString>
void myqsortm(QVector <measured>& measureds, int l, int r)
{
    int i = l, j = r;
    measured k;
    QString opora = measureds[(l + r) / 2].name;
    while (i < j)
    {
        while ((measureds[i].name < opora))
            i++;
        while ((measureds[j].name > opora))
            j--;
        if (i < j)
        {
            k = measureds[i];
            measureds[i]=measureds[j];
            measureds[j]=k;
            i++;
            j--;
        }
    }
    if (r - l == 1)
        i++;
    if (l < j)
        myqsortm(measureds,l, j);
    if (r > i)
        myqsortm(measureds,i, r);
}
