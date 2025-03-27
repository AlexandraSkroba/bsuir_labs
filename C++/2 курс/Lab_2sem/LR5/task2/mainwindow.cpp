#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0,0,600,400,this);
    ui->graphicsView->setScene(scene);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setFixedSize(600,400);

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->comboBox->addItems(QStringList() << "push_back" << "push_front" << "pop_back" << "pop_front" << "size" << "empty" << "clear" << "resize" << "front" << "back");

    ui->NewSize->setAlignment(Qt::AlignCenter);
    ui->Value->setAlignment(Qt::AlignCenter);

    ui->Value->setRange(-10000,10000);
    ui->NewSize->setRange(0,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Open_clicked()
{
    int i = ui->comboBox->currentIndex();

    switch(i){
    case 0:
        push_back();
        break;
    case 1:
        push_front();
        break;
    case 2:
        pop_back();
        break;
    case 3:
        pop_front();
        break;
    case 4:
        DequeSize();
        break;
    case 5:
        DequeEmpty();
        break;
    case 6:
        clear();
        break;
    case 7:
        resize();
        break;
    case 8:
        DequeFront();
        break;
    case 9:
        DequeBack();
        break;
    }
}

void MainWindow::push_back()
{
    ui->textEdit->clear();
    int num = rand() % 200 - 100;

    deq.push_back(num);
    for(int i=0;i<deq.size();i++){
        QString tmp;
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(tmp.setNum(deq[i]));
    }
}

void MainWindow::push_front()
{
    ui->textEdit->clear();
    int num = rand() % 200 - 100;
    deq.push_front(num);
    for(int i=0;i<deq.size();i++){
        QString tmp;
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(tmp.setNum(deq[i]));
    }
}

void MainWindow::pop_back()
{
    if(deq.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Deque is empty.\nAdd elements");
        return;
    }
    ui->textEdit->clear();
    deq.pop_back();
    for(int i=0;i<deq.size();i++){
        QString tmp;
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(tmp.setNum(deq[i]));
    }
}

void MainWindow::pop_front()
{
    if(deq.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Deque is empty.\nAdd elements");
        return;
    }
    ui->textEdit->clear();
    deq.pop_front();
    for(int i=0;i<deq.size();i++){
        QString tmp;
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(tmp.setNum(deq[i]));
    }
}

void MainWindow::DequeSize()
{
    QString size;
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("\nDeque size is " + size.setNum(deq.size()));
}

void MainWindow::DequeEmpty()
{
    if(deq.empty()){
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append("\nDeque is empty");
    } else {
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append("\nDeque is not empty");
    }
}

void MainWindow::clear()
{
    deq.clear();
    ui->textEdit->clear();
    QString size;
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("\nDeque size is " + size.setNum(deq.size()));
}

void MainWindow::resize()
{
    ui->textEdit->clear();

    int count = ui->NewSize->value();
    int value = ui->Value->value();
    deq.resize(count,value);

    for(int i=0;i<deq.size();i++){
        QString tmp;
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(tmp.setNum(deq[i]));
    }

    QString size;
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("\nDeque size is " + size.setNum(deq.size()));
}

void MainWindow::DequeFront()
{
    if(deq.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Deque is empty.\nAdd elements");
        return;
    }
    ui->textEdit->clear();
    auto it = deque<int>::Iterator(deq.front());
    QString first;
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("\nFrist is " + first.setNum(*it));
}

void MainWindow::DequeBack()
{
    if(deq.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Deque is empty.\nAdd elements");
        return;
    }
    ui->textEdit->clear();
    auto it = deque<int>::Iterator(deq.back());
    QString last;
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("\nFrist is " + last.setNum(*it));
}


void MainWindow::on_Close_clicked()
{
    this->close();
}

