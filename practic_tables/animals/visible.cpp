#include "visible.h"

visible::visible()
{
    this->name="";
    this->color ="";
    this->feet = 0;
}
visible::visible(QString n,QString c,double m)
{
    this->name=n;
    this->color =c;
    this->feet = m;
}
QTextStream& operator>>(QTextStream& in,visible& a)
{
    in >> a.name;
    in >> a.color;
    in >> a.feet;
    return in;
}
QDataStream& operator>>(QDataStream& in,visible& a)
{
    in >> a.name;
    in >> a.color;
    in >> a.feet;
    return in;
}
QTextStream& operator<<(QTextStream& out,visible& a)
{
    out << a.name <<"\n";
    out <<a.color <<"\n";
    out << a.feet <<"\n";
    return out;
}
QDataStream& operator<<(QDataStream& out,visible& a)
{
    out << a.name;
    out <<a.color;
    out << a.feet;
    return out;
}
