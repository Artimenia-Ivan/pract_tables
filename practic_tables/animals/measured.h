#ifndef MEASURED_H
#define MEASURED_H
#include <QString>
#include <QTextStream>
#include <QDataStream>
struct measured
{
    QString name;
    double mass;
    double size;
    double speed;
    measured();
    measured(QString n,double m,double si,double sp);
    friend QTextStream& operator>>(QTextStream& in,measured& a);
    friend QDataStream& operator>>(QDataStream& in,measured& a);
    friend QTextStream& operator<<(QTextStream& in,measured& a);
    friend QDataStream& operator<<(QDataStream& in,measured& a);
};
#endif // MEASURED_H


