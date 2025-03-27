#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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


void MainWindow::on_mapInsert_clicked()
{
    int key = ui->mapKey->value();
    int value = ui->mapValue->value();
    mp[key] = value;
}


void MainWindow::on_mapCount_clicked()
{
    int key = ui->mapCountKey->value();
    int count = mp.count(key);
    ui->mapDisplay->append("count of " + QString::number(key) + " is " + QString::number(count));
}


void MainWindow::on_mapErase_clicked()
{
    int key = ui->mapEraseKey->value();
    if(key > mp.size()){
        return;
    }
    mp.erase(key);
}


void MainWindow::on_mapAt_clicked()
{
    int key = ui->mapAtKey->value();
    int value = mp[key];
    ui->mapDisplay->append("value under the key is " + QString::number(value));
}


void MainWindow::on_mapClear_clicked()
{
    mp.clear();
}


void MainWindow::on_mapPrintAll_clicked()
{
    QString ans = mp.toString();
    ui->mapDisplay->append(ans.isEmpty() ? "Empty" : ans);
}


void MainWindow::on_mapSize_clicked()
{
    ui->mapDisplay->append("size is " + QString::number(mp.size()));
}

