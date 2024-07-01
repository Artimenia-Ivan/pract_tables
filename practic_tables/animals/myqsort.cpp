#include "myqsort.h"
#include "visible.h"
#include <QVector>
#include <QString>
void myqsort(QVector <visible>& visibles, int l, int r)
{
    int i = l, j = r;
    visible k;
    QString opora = visibles[(l + r) / 2].name;
    while (i < j)
    {
        while ((visibles[i].name < opora))
            i++;
        while ((visibles[j].name > opora))
            j--;
        if (i < j)
        {
            k = visibles[i];
            visibles[i]=visibles[j];
            visibles[j]=k;
            i++;
            j--;
        }
    }
    if (r - l == 1)
        i++;
    if (l < j)
        myqsort(visibles,l, j);
    if (r > i)
        myqsort(visibles,i, r);
}
