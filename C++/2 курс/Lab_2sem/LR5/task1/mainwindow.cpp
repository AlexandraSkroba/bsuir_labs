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

    ui->comboBox->addItems(QStringList() << "push" << "pop" << "size" << "empty" << "front" << "back" << "emplace" << "swap");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Do_clicked()
{
    int i = ui->comboBox->currentIndex();

    switch(i){
    case 0:
        push();
        break;
    case 1:
        pop();
        break;
    case 2:
        size();
        break;
    case 3:
        empty();
        break;
    case 4:
        front();
        break;
    case 5:
        back();
        break;
    case 6:
        emplace();
        break;
    case 7:
        swap();
        break;
    }
}

void MainWindow::push()
{
    ui->queue1->clear();
    int num = rand() % 200 - 100;
    q1.push(num);
    for(int i=0;i<q1.size();i++){
        QString tmp;
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append(tmp.setNum(q1[i]));
    }
}

void MainWindow::pop()
{
    if(q1.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Queue is empty.\nAdd elements");
        return;
    }
    ui->queue1->clear();
    q1.pop();
    for(int i=0;i<q1.size();i++){
        QString tmp;
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append(tmp.setNum(q1[i]));
    }
}

void MainWindow::size()
{
    QString size;
    ui->queue1->setAlignment(Qt::AlignCenter);
    ui->queue1->append("\nQueue size is " + size.setNum(q1.size()));
}

void MainWindow::empty()
{
    if(q1.empty()){
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append("\nQueue is empty");
    } else {
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append("\nQueue is not empty");
    }
}

void MainWindow::front()
{
    if(q1.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Queue is empty.\nAdd elements");
        return;
    }

    auto it = queue<int>::Iterator(q1.front());
    ui->queue1->clear();

    QString first;
    first.setNum(*it);

    ui->queue1->setAlignment(Qt::AlignCenter);
    ui->queue1->append("\nThe first element is  " + first);
}

void MainWindow::back()
{
    if(q1.size() == 0){
        QMessageBox m;
        m.warning(this,"Error","Queue is empty.\nAdd elements");
        return;
    }

    auto it = queue<int>::Iterator(q1.back());
    ui->queue1->clear();

    QString last;
    last.setNum(*it);

    ui->queue1->setAlignment(Qt::AlignCenter);
    ui->queue1->append("\nThe first element is  " + last);
}

void MainWindow::emplace()
{
    ui->queue1->clear();
    int num = rand() % 200 - 100;
    q1.emplace(num);
    for(int i=0;i<q1.size();i++){
        QString tmp;
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append(tmp.setNum(q1[i]));
    }
}

void MainWindow::swap()
{
    ui->queue1->clear();
    ui->queue2->clear();

    q1.swap(q2);

    for(int i=0;i<q1.size();i++){
        QString tmp;
        ui->queue1->setAlignment(Qt::AlignCenter);
        ui->queue1->append(tmp.setNum(q1[i]));
    }

    for(int i=0;i<q2.size();i++){
        QString tmp;
        ui->queue2->setAlignment(Qt::AlignCenter);
        ui->queue2->append(tmp.setNum(q2[i]));
    }
}

void MainWindow::on_Task_clicked()
{
    this->hide();
    app = new Application();
    app->show();
}


void MainWindow::on_Close_clicked()
{
    this->close();
}

