#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <regex>
#include <QDebug>
#include <stack>
#include <QLibrary>
#include<iostream>
#include<QDebug>

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

void MainWindow::on_pushButtonLine_clicked()
{
    code = ui->textEdit->toPlainText();

    std::regex regular1("[0-9]{2}\\.[0-9]{2}\\s(Mon|Tue|Wed|Thu|Fri|Sat|Sun)\\s[0-9]{2}:[0-9]{2}");
    std::regex regular2("((>[0-9]{2}\\s(days))|(>[0-9]{3}\\s(days))|(>[0-9]\\s(days))|(>[0-9]{2}:[0-9]{2}))");
    std::regex regular3("((^[0-9]{2}\\s(days))|(^[0-9]\\s(days))|(^[0-9]{2}:[0-9]{2}:[0-9]{2}))");
    std::regex regular_name("(^<a class=\"title_search\".+<)");
    std::smatch result;

    temp = code.toStdString();

    //date1
    while(std::regex_search(temp, result, regular1))
    {
        date1.push_back(result.str());
        temp = result.suffix();
    }
   // spare += "Start/End Time:\n";
    /*for(int i =0;i<date1.size();i++){
        spare += QString::fromStdString(date1[i]) + "\n";
    }*/
    temp = code.toStdString();

    //date2
    while(std::regex_search(temp, result, regular2))
    {
        std::string buf = result.str();
        if(buf[0] == '>' ) {
            buf.erase(0, 1);
        }
        date2.push_back(buf);
        temp = result.suffix();
    }
   // spare += "Duration:\n";
    /*for(int i =0;i<date2.size();i++){
        spare += QString::fromStdString(date2[i]) + "\n";
    }*/
    temp = code.toStdString();

    //date3
    while(std::regex_search(temp, result, regular3))
    {
        date3.push_back(result.str());
        temp = result.suffix();
    }
    //spare += "Time Left:\n";
    /*for(int i =0;i<date3.size();i++){
        spare += QString::fromStdString(date3[i]) + "\n";
    }*/
    temp = code.toStdString();

    //name
    while(std::regex_search(temp, result, regular_name))
    {
        std::string buf = result.str();
        buf.erase(0,38);
        while(buf[0] != '>'){
            buf.erase(0,1);
        }
        buf.erase(0,1);
        buf.erase(buf.size()-1, 1);

        name.push_back(buf);
        temp = result.suffix();
    }
   // spare += "Event:\n";
    for(int i =0;i<name.size();i++){
        spare += QString::number(i+1) + ")" + " " +  QString::fromStdString(date1[i]) + " | " + QString::fromStdString(date2[i]) + " | "  + QString::fromStdString(date3[i]) + " | "  + QString::fromStdString(name[i]) +  "\n\n";
    }
    temp = code.toStdString();
    /*-------------------------------------------------------------------------------------------------------------*/

    ui->textBrowser->setText(spare);
    spare.clear();
    date1.clear();
    date2.clear();
    date3.clear();
    name.clear();
    code.clear();
}

