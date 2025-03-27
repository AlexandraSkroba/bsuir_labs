#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_setInsert_clicked()
{
    s.insert(ui->setInsertValue->value());
}


void MainWindow::on_setCount_clicked()
{
    int num = ui->setCountValue->value();
    int count = s.count(num);
    ui->setDisplay->append("count of " + QString::number(num) + " is " + QString::number(count));
}


void MainWindow::on_setErase_clicked()
{
    s.erase(ui->setEraseValue->value());
}


void MainWindow::on_setClear_clicked()
{
    s.clear();
}


void MainWindow::on_setSize_clicked()
{
    int size = s.size();
    ui->setDisplay->append("size of set is " + QString::number(size));
}


void MainWindow::on_setPrint_clicked()
{
    QString ans;
    for (auto& val : s){
        ans += QString::number(val) + " ";
    }
    ui->setDisplay->append(ans.isEmpty() ? "Empty" : ans);
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
    QString ans;
    for (auto p : mp){
        ans += "mp[" + QString::number(p.first) + "] = " + QString::number(p.second) + " ";
    }
    ui->mapDisplay->append(ans.isEmpty() ? "Empty" : ans);
}


void MainWindow::on_mapSize_clicked()
{
    ui->mapDisplay->append("size is " + QString::number(mp.size()));
}
