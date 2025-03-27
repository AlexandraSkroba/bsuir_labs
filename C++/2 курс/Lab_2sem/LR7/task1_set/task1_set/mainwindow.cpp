#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox_set->addItems(QStringList() << " insert " << " erase " << " size " << " empty " << " find " << " contains " << " clear " << " begin " << " back " << " emplace " << " lower_bound " << " upper_bound ");

    ui->spinBox_set->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertSet()
{
    int key = ui->spinBox_set->value();
    if(m_set.contains(key)){
        QMessageBox m;
        m.warning(this,"Error","Set already has such key.\nAdd another key");
        return;
    }
    m_set.insert(key);
}

void MainWindow::eraseSet()
{
    if(!m_set.size()){
        QMessageBox m;
        m.warning(this,"Error","Set is empty.\nAdd elements");
        return;
    }
    int key = ui->spinBox_set->value();
    if(m_set.contains(key)){
        m_set.erase(key);
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in set.\nChoose another key");
        return;
    }
}

void MainWindow::sizeSet()
{
    ui->InfoSet->clear();
    int size = m_set.size();
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("Size of set is " + s.setNum(size));
}

void MainWindow::emptySet()
{
    ui->InfoSet->clear();
    if(m_set.empty()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Set is empty");
    }
    else{
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Set is not empty");
    }
}

void MainWindow::findSet()
{
    ui->InfoSet->clear();
    int key = ui->spinBox_set->value();
    if(m_set.contains(key)){
         auto it = set<int>::BSTIterator(m_set.find(key));
         QString s;
         ui->InfoSet->setAlignment(Qt::AlignCenter);
         ui->InfoSet->setText("The key " + s.setNum(key) + " exists");
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in set.\nChoose another key");
        return;
    }
}

void MainWindow::containsSet()
{
    ui->InfoSet->clear();
    int key = ui->spinBox_set->value();
    if(m_set.contains(key)){
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Set contains the key " + s.setNum(key));
    } else {
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Set doesn't contain the key " + s.setNum(key));
    }
}

void MainWindow::clearSet()
{
    ui->InfoSet->clear();
    if(!m_set.size()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Set is already empty");
    } else {
        m_set.clear();
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Size of set is " + s.setNum(m_set.size()));
    }
}

void MainWindow::beginSet()
{
    ui->InfoSet->clear();
    if(!m_set.size()){
        QMessageBox m;
        m.warning(this,"Error","Set is empty.\nAdd elements");
        return;
    }
    auto it = set<int>::BSTIterator(m_set.begin());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The first key of set is " + s.setNum(*it));
}

void MainWindow::backSet()
{
    ui->InfoSet->clear();
    if(!m_set.size()){
        QMessageBox m;
        m.warning(this,"Error","Set is empty.\nAdd elements");
        return;
    }
    auto it = set<int>::BSTIterator(m_set.back());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The last key of set is " + s.setNum(*it));
}

void MainWindow::emplaceSet()
{
    insertSet();
}

void MainWindow::lower_boundSet()
{
    ui->InfoSet->clear();
    if(!m_set.size()){
        QMessageBox m;
        m.warning(this,"Error","Set is empty.\nAdd elements");
        return;
    }
    int key = ui->spinBox_set->value();
    auto it = set<int>::BSTIterator(m_set.lower_bound(key));
    if(it != nullptr){
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("The first element not less than the given key is " + s.setNum(*it));
    } else {
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("There is no one element not less than the given key is");
    }
}

void MainWindow::upper_boundSet()
{
    ui->InfoSet->clear();
    if(!m_set.size()){
        QMessageBox m;
        m.warning(this,"Error","Set is empty.\nAdd elements");
        return;
    }
    int key = ui->spinBox_set->value();
    auto it = set<int>::BSTIterator(m_set.upper_bound(key));
    if(it != nullptr){
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("The first element greater than the given key is " + s.setNum(*it));
    } else {
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("There is no one element greater than the given key is");
    }
}

void MainWindow::print()
{
    ui->MainSet->clear();
    m_set.print();
    ui->MainSet->setText(m_set.S);
}


void MainWindow::on_do_set_clicked()
{
    int i = ui->comboBox_set->currentIndex();

    switch(i){
    case 0:
        insertSet();
        print();
        break;
    case 1:
        eraseSet();
        print();
        break;
    case 2:
        sizeSet();
        break;
    case 3:
        emptySet();
        break;
    case 4:
        findSet();
        break;
    case 5:
        containsSet();
        break;
    case 6:
        clearSet();
        print();
        break;
    case 7:
        beginSet();
        break;
    case 8:
        backSet();
        break;
    case 9:
        emplaceSet();
        print();
        break;
    case 10:
        lower_boundSet();
        break;
    case 11:
        upper_boundSet();
        break;
    }
}
