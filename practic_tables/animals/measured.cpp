#include "measured.h"

measured::measured()
{
    this->name="";
    this->mass =0;
    this->size = 0;
    this->speed = 0;
}
measured::measured(QString n,double m,double si,double sp)
{
    this->name=n;
    this->mass =m;
    this->size = si;
    this->speed = sp;
}
QTextStream& operator>>(QTextStream& in,measured& a)
{
    in >> a.name;
    in >> a.mass;
    in >> a.size;
    in >> a.speed;
    return in;
}
QDataStream& operator>>(QDataStream& in,measured& a)
{
    in >> a.name;
    in >> a.mass;
    in >> a.size;
    in >> a.speed;
    return in;
}
QTextStream& operator<<(QTextStream& out,measured& a)
{
    out << a.name <<"\n";
    out <<a.mass <<"\n";
    out << a.size <<"\n";
    out << a.speed <<"\n";
    return out;
}
QDataStream& operator<<(QDataStream& out,measured& a)
{
    out << a.name;
    out <<a.mass;
    out << a.size;
    out << a.speed;
    return out;
}
