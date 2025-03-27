#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0,0,600,400,this);
    ui->graphicsView->setScene(scene);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setFixedSize(600,400);

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Application::~Application()
{
    delete ui;
}

void Application::on_FullFill_clicked()
{
    srand(time(NULL));
    for(int i = 0;i<2;i++){
        int num = rand() % 200 - 100;
        mainQ.push(num);
        QString s;
        ui->mainQueue->setAlignment(Qt::AlignCenter);
        ui->mainQueue->append(s.setNum(num));
    }
}


void Application::on_Open_clicked()
{
    auto it = queue<int>::Iterator(mainQ.front());
    while(mainQ.size()){
        auto item = *it;
        it++;
        mainQ.pop();
        if(item>=0){
            subQ1.push(item);
        } else {
            subQ2.push(item);
        }
    }

    ui->subQ1->clear();
    for(int i=0;i<subQ1.size();i++){
        QString tmp;
        ui->subQ1->setAlignment(Qt::AlignCenter);
        ui->subQ1->append(tmp.setNum(subQ1[i]));
    }

    ui->subQ2->clear();
    for(int i=0;i<subQ2.size();i++){
        QString tmp;
        ui->subQ2->setAlignment(Qt::AlignCenter);
        ui->subQ2->append(tmp.setNum(subQ2[i]));
    }
}


void Application::on_Close_clicked()
{
    this->close();
}

