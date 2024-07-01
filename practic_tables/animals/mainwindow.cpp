#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visible.h"
#include "measured.h"
#include "myqsort.h"
#include "myqsortm.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
QVector <visible> visibles;
QVector <measured> measureds;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int n = visibles.size();
    QStandardItemModel* model=  new QStandardItemModel(n, 3);
    for(int i =0;i<n;i++)
    {
        model->setItem(i, 0, new QStandardItem(visibles[i].name));
        model->setItem(i, 1, new QStandardItem(visibles[i].color));
        model->setItem(i, 2, new QStandardItem(QString::number(visibles[i].feet)));
    }
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Color");
    model->setHeaderData(2, Qt::Horizontal, "feet");
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,80);
}

void MainWindow::on_pushButton_2_clicked()
{
    visible k;
    k.name = ui->lineEdit ->text();
    k.color = ui->lineEdit_2 ->text();
    k.feet = ui->lineEdit_3 ->text().toDouble();
    visibles.push_back(k);
    on_pushButton_clicked();
}


void MainWindow::on_pushButton_3_clicked()
{
    myqsort(visibles, 0, visibles.size()-1);
    on_pushButton_clicked();
}


void MainWindow::on_pushButton_4_clicked()
{
    QFile txtvisibles("visibles.txt");
    if(txtvisibles.open(QIODevice::WriteOnly))
    {
        QTextStream out(&txtvisibles);
        int n = visibles.size();
        out << n << "\n";
        for(int i=0;i<n;i++)
        {
            out << visibles[i];
        }
        txtvisibles.close();
    }
}
void MainWindow::on_pushButton_5_clicked()
{
    QFile binvisibles("visibles.bin");
    if(binvisibles.open(QIODevice::ReadWrite))
    {
        QDataStream out(&binvisibles);
        int n = visibles.size();
        out << n;
        for(int i=0;i<n;i++)
        {
            out << visibles[i];
        }
        binvisibles.close();
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QFile txtvisibles("visibles.txt");
    if(txtvisibles.open(QIODevice::ReadOnly))
    {
        QTextStream in(&txtvisibles);
        visibles.clear();
        visible k;
        int n;
        in >>n;
        for(int i=0;i<n;i++)
        {
            in >> k;
            visibles.push_back(k);
        }
        txtvisibles.close();
    }
    on_pushButton_clicked();
}


void MainWindow::on_pushButton_7_clicked()
{
    QFile binvisibles("visibles.bin");
    if(binvisibles.open(QIODevice::ReadWrite))
    {
        QDataStream in(&binvisibles);
        visibles.clear();
        int n;
        in >> n;
        visible k;
        for(int i=0;i<n;i++)
        {
            in >> k;
            visibles.push_back(k);
        }
        binvisibles.close();
    }
    on_pushButton_clicked();
}


void MainWindow::on_pushButton_8_clicked()
{
    int k = ui->lineEdit_4 ->text().toInt();
    visibles.erase(visibles.begin()+k-1);
    on_pushButton_clicked();
}
void MainWindow::on_pushButton_9_clicked()
{
    myqsort(visibles, 0, visibles.size()-1);
    QString s = ui->lineEdit_5 ->text();
    int l = visibles.size();
    int k= l/2;
    int k1=0;
    int k2= l-1;
    do
    {
        if(s>visibles[k].name)
        {
            k1 = k;
            k = (k1+k2)/2;
        }
        else
        {
            if(s<visibles[k].name)
            {
                k2 = k;
                k = (k1+k2)/2;
            }
        }
    }
    while(visibles[k].name!=s&&(k2-k1)>2);
    for(int i=k1;i<=k2;i++)
    {
        if(visibles[i].name == s)
        {
            k=i;
            break;
        }
    }
    if(visibles[k].name==s)
    {
        k1 =k;
        k2= k;
        while(visibles[k1].name==s&&k1>0)
        {
            k1--;
        }
        if(k1==0)
        {
            if(visibles[0].name==s)
            {
                k1=0;
            }
            else
            {
                k1=1;
            }
        }
        else
        {
            k1++;
        }
        while(visibles[k2].name==s&&k2<l-1)
        {
            k2++;
        }
        if(k2==l-1)
        {
            if(visibles[l-1].name==s)
            {
                k2=l-1;
            }
            else
            {
                k2=l-2;
            }
        }
        else
        {
            k2--;
        }
        QStandardItemModel* model=  new QStandardItemModel(k2-k1+1, 3);
        for(int i =0;i<=k2-k1;i++)
        {
            model->setItem(i, 0, new QStandardItem(visibles[i+k1].name));
            model->setItem(i, 1, new QStandardItem(visibles[i+k1].color));
            model->setItem(i, 2, new QStandardItem(QString::number(visibles[i+k1].feet)));
        }
        model->setHeaderData(0, Qt::Horizontal, "Name");
        model->setHeaderData(1, Qt::Horizontal, "Color");
        model->setHeaderData(2, Qt::Horizontal, "feet");
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,100);
        ui->tableView->setColumnWidth(2,80);
    }
    else
    {
        QStandardItemModel* model=  new QStandardItemModel(1, 1);
        model->setItem(0, 0, new QStandardItem("There is no elements"));\
            ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,280);
    }
}


void MainWindow::on_comboBox_activated(int index)
{
    if(index==0)
    {
        ui-> lineEdit_6 -> setVisible(0);
        ui-> pushButton -> setVisible(1);
        ui-> pushButton_2 -> setVisible(1);
        ui-> pushButton_3 -> setVisible(1);
        ui-> pushButton_4 -> setVisible(1);
        ui-> pushButton_5 -> setVisible(1);
        ui-> pushButton_6 -> setVisible(1);
        ui-> pushButton_7 -> setVisible(1);
        ui-> pushButton_8 -> setVisible(1);
        ui-> pushButton_9 -> setVisible(1);
        ui-> pushButton_10 -> setVisible(0);
        ui-> pushButton_11 -> setVisible(0);
        ui-> pushButton_12 -> setVisible(0);
        ui-> pushButton_13 -> setVisible(0);
        ui-> pushButton_14 -> setVisible(0);
        ui-> pushButton_15 -> setVisible(0);
        ui-> pushButton_16 -> setVisible(0);
        ui-> pushButton_17 -> setVisible(0);
        ui-> pushButton_18 -> setVisible(0);
    }
    if(index==1)
    {
        ui-> lineEdit_6 -> setVisible(1);
        ui-> pushButton_2 -> setVisible(0);
        ui-> pushButton_3 -> setVisible(0);
        ui-> pushButton_4 -> setVisible(0);
        ui-> pushButton_5 -> setVisible(0);
        ui-> pushButton_6 -> setVisible(0);
        ui-> pushButton_7 -> setVisible(0);
        ui-> pushButton_8 -> setVisible(0);
        ui-> pushButton_9 -> setVisible(0);
        ui-> pushButton_10 -> setVisible(1);
        ui-> pushButton_11 -> setVisible(1);
        ui-> pushButton_12 -> setVisible(1);
        ui-> pushButton_13 -> setVisible(1);
        ui-> pushButton_14 -> setVisible(1);
        ui-> pushButton_15 -> setVisible(1);
        ui-> pushButton_16 -> setVisible(1);
        ui-> pushButton_17 -> setVisible(1);
        ui-> pushButton_18 -> setVisible(1);
    }
}


void MainWindow::on_pushButton_18_clicked()
{
    int n = measureds.size();
    QStandardItemModel* model=  new QStandardItemModel(n, 4);
    for(int i =0;i<n;i++)
    {
        model->setItem(i, 0, new QStandardItem(measureds[i].name));
        model->setItem(i, 1, new QStandardItem(QString::number(measureds[i].mass)));
        model->setItem(i, 2, new QStandardItem(QString::number(measureds[i].size)));
        model->setItem(i, 3, new QStandardItem(QString::number(measureds[i].speed)));
    }
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Mass");
    model->setHeaderData(2, Qt::Horizontal, "size");
    model->setHeaderData(3, Qt::Horizontal, "speed");
    ui->tableView_2->setModel(model);
    ui->tableView_2->setColumnWidth(0,100);
    ui->tableView_2->setColumnWidth(1,80);
    ui->tableView_2->setColumnWidth(2,80);
    ui->tableView_2->setColumnWidth(3,80);
}


void MainWindow::on_pushButton_10_clicked()
{
    measured k;
    k.name = ui->lineEdit ->text();
    k.mass = ui->lineEdit_2 ->text().toDouble();
    k.size = ui->lineEdit_3 ->text().toDouble();
    k.speed = ui->lineEdit_6 ->text().toDouble();
    measureds.push_back(k);
    on_pushButton_18_clicked();
}


void MainWindow::on_pushButton_11_clicked()
{
    myqsortm(measureds, 0, measureds.size()-1);
    on_pushButton_18_clicked();
}


void MainWindow::on_pushButton_12_clicked()
{
    QFile txtmeasureds("measureds.txt");
    if(txtmeasureds.open(QIODevice::WriteOnly))
    {
        QTextStream out(&txtmeasureds);
        int n = measureds.size();
        out << n << "\n";
        for(int i=0;i<n;i++)
        {
            out << measureds[i];
        }
        txtmeasureds.close();
    }
}
void MainWindow::on_pushButton_13_clicked()
{
    QFile binmeasureds("measureds.bin");
    if(binmeasureds.open(QIODevice::ReadWrite))
    {
        QDataStream out(&binmeasureds);
        int n = measureds.size();
        out << n;
        for(int i=0;i<n;i++)
        {
            out << measureds[i];
        }
        binmeasureds.close();
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    QFile txtmeasureds("measureds.txt");
    if(txtmeasureds.open(QIODevice::ReadOnly))
    {
        QTextStream in(&txtmeasureds);
        measureds.clear();
        measured k;
        int n;
        in >>n;
        for(int i=0;i<n;i++)
        {
            in >> k;
            measureds.push_back(k);
        }
        txtmeasureds.close();
    }
    on_pushButton_18_clicked();
}


void MainWindow::on_pushButton_15_clicked()
{
    QFile binmeasureds("measureds.bin");
    if(binmeasureds.open(QIODevice::ReadWrite))
    {
        QDataStream in(&binmeasureds);
        measureds.clear();
        int n;
        in >> n;
        measured k;
        for(int i=0;i<n;i++)
        {
            in >> k;
            measureds.push_back(k);
        }
        binmeasureds.close();
    }
    on_pushButton_18_clicked();
}


void MainWindow::on_pushButton_16_clicked()
{
    int k = ui->lineEdit_4 ->text().toInt();
    measureds.erase(measureds.begin()+k-1);
    on_pushButton_18_clicked();
}
void MainWindow::on_pushButton_17_clicked()
{
    myqsortm(measureds, 0, measureds.size()-1);
    QString s = ui->lineEdit_5 ->text();
    int l = measureds.size();
    int k= l/2;
    int k1=0;
    int k2= l-1;
    do
    {
        if(s>measureds[k].name)
        {
            k1 = k;
            k = (k1+k2)/2;
        }
        else
        {
            if(s<measureds[k].name)
            {
                k2 = k;
                k = (k1+k2)/2;
            }
        }
    }
    while(measureds[k].name!=s&&(k2-k1)>2);
    for(int i=k1;i<=k2;i++)
    {
        if(measureds[i].name == s)
        {
            k=i;
            break;
        }
    }
    if(measureds[k].name==s)
    {
        k1 =k;
        k2= k;
        while(measureds[k1].name==s&&k1>0)
        {
            k1--;
        }
        if(k1==0)
        {
            if(measureds[0].name==s)
            {
                k1=0;
            }
            else
            {
                k1=1;
            }
        }
        else
        {
            k1++;
        }
        while(measureds[k2].name==s&&k2<l-1)
        {
            k2++;
        }
        if(k2==l-1)
        {
            if(measureds[l-1].name==s)
            {
                k2=l-1;
            }
            else
            {
                k2=l-2;
            }
        }
        else
        {
            k2--;
        }
        QStandardItemModel* model=  new QStandardItemModel(k2-k1+1, 4);
        for(int i =0;i<k2-k1;i++)
        {
            model->setItem(i, 0, new QStandardItem(measureds[i].name));
            model->setItem(i, 1, new QStandardItem(measureds[i].mass));
            model->setItem(i, 2, new QStandardItem(QString::number(measureds[i].size)));
            model->setItem(i, 3, new QStandardItem(QString::number(measureds[i].speed)));
        }
        model->setHeaderData(0, Qt::Horizontal, "Name");
        model->setHeaderData(1, Qt::Horizontal, "Mass");
        model->setHeaderData(2, Qt::Horizontal, "size");
        model->setHeaderData(3, Qt::Horizontal, "speed");
        ui->tableView_2->setModel(model);
        ui->tableView_2->setColumnWidth(0,100);
        ui->tableView_2->setColumnWidth(1,80);
        ui->tableView_2->setColumnWidth(2,80);
        ui->tableView_2->setColumnWidth(3,80);
    }
    else
    {
        QStandardItemModel* model=  new QStandardItemModel(1, 1);
        model->setItem(0, 0, new QStandardItem("There is no elements"));\
            ui->tableView_2->setModel(model);
        ui->tableView_2->setColumnWidth(0,340);
    }
}


void MainWindow::on_pushButton_19_clicked()
{
    myqsort(visibles, 0, visibles.size()-1);
    myqsortm(measureds, 0, measureds.size()-1);
    int l1 = visibles.size()-1;
    int l2 = measureds.size()-1;
    int k1=0;
    int k2=0;
    int c=0;
    QStandardItemModel* model2=  new QStandardItemModel(c, 6);
    while(k1<=l1&&k2<=l2)
    {
        if(visibles[k1].name==measureds[k2].name)
        {
            model2->setItem(c, 0, new QStandardItem(visibles[k1].name));
            model2->setItem(c, 1, new QStandardItem(visibles[k1].color));
            model2->setItem(c, 2, new QStandardItem(QString::number(visibles[k1].feet)));
            model2->setItem(c, 3, new QStandardItem(QString::number(measureds[k2].mass)));
            model2->setItem(c, 4, new QStandardItem(QString::number(measureds[k2].size)));
            model2->setItem(c, 5, new QStandardItem(QString::number(measureds[k2].speed)));
            c++;
            k1++;
            k2++;
        }
        else
        {
            if(visibles[k1].name>measureds[k2].name)
            {
                model2->setItem(c, 0, new QStandardItem(measureds[k2].name));
                model2->setItem(c, 3, new QStandardItem(QString::number(measureds[k2].mass)));
                model2->setItem(c, 4, new QStandardItem(QString::number(measureds[k2].size)));
                model2->setItem(c, 5, new QStandardItem(QString::number(measureds[k2].speed)));
                c++;
                k2++;
            }
            else
            {
                model2->setItem(c, 0, new QStandardItem(visibles[k1].name));
                model2->setItem(c, 1, new QStandardItem(visibles[k1].color));
                model2->setItem(c, 2, new QStandardItem(QString::number(visibles[k1].feet)));
                c++;
                k1++;
            }
        }
    }
    while(k1<=l1)
    {
        model2->setItem(c, 0, new QStandardItem(visibles[k1].name));
        model2->setItem(c, 1, new QStandardItem(visibles[k1].color));
        model2->setItem(c, 2, new QStandardItem(QString::number(visibles[k1].feet)));
        c++;
        k1++;
    }
    while(k2<=l2)
    {
        model2->setItem(c, 0, new QStandardItem(measureds[k2].name));
        model2->setItem(c, 3, new QStandardItem(QString::number(measureds[k2].mass)));
        model2->setItem(c, 4, new QStandardItem(QString::number(measureds[k2].size)));
        model2->setItem(c, 5, new QStandardItem(QString::number(measureds[k2].speed)));
        c++;
        k2++;
    }

    if(c==0)
    {
        QStandardItemModel* model=  new QStandardItemModel(1, 1);
        model->setItem(0, 0, new QStandardItem("There is no elements"));
        ui->tableView_3->setModel(model);
        ui->tableView_3->setColumnWidth(0,520);
    }
    else
    {
        model2->setHeaderData(0, Qt::Horizontal, "Name");
        model2->setHeaderData(1, Qt::Horizontal, "Color");
        model2->setHeaderData(2, Qt::Horizontal, "Feet");
        model2->setHeaderData(3, Qt::Horizontal, "Mass");
        model2->setHeaderData(4, Qt::Horizontal, "Size");
        model2->setHeaderData(5, Qt::Horizontal, "Speed");
        ui->tableView_3->setModel(model2);
        ui->tableView_3->setColumnWidth(0,100);
        ui->tableView_3->setColumnWidth(1,100);
        ui->tableView_3->setColumnWidth(2,80);
        ui->tableView_3->setColumnWidth(3,80);
        ui->tableView_3->setColumnWidth(4,80);
        ui->tableView_3->setColumnWidth(5,80);
    }
}

