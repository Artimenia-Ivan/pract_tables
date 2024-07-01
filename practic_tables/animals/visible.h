#ifndef VISIBLE_H
#define VISIBLE_H
#include <QString>
#include <QTextStream>
#include <QDataStream>
struct visible
{
    QString name;
    QString color;
    double feet;
    visible();
    visible(QString n,QString c,double f);
    friend QTextStream& operator>>(QTextStream& in,visible& a);
    friend QDataStream& operator>>(QDataStream& in,visible& a);
    friend QTextStream& operator<<(QTextStream& in,visible& a);
    friend QDataStream& operator<<(QDataStream& in,visible& a);
};

#endif
