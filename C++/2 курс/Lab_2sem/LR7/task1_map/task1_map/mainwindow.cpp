#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(361,255);

    ui->comboBox_map->addItems(QStringList() << " insert " << " insert_or_assing " << " erase " << " size " << " empty " << " find " << " contains " << " clear " << " begin " << " back " << " lower_bound " << " upper_bound ");

    ui->spinBox_map->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertMap()
{
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    int data = ui->spinBox_map->value();
    if(m_map.contains(key.toStdString())){
        QMessageBox m;
        m.warning(this,"Error","Map already has such key.\nAdd another key");
        return;
    }
    pair<std::string,int> m_pair;
    m_pair.first = key.toStdString();
    m_pair.second = data;
    m_map.insert(m_pair);
}

void MainWindow::insert_or_assignMap()
{
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    int data = ui->spinBox_map->value();
    pair<std::string,int> m_pair;
    m_pair.first = key.toStdString();
    m_pair.second = data;
    m_map.insert_or_assign(m_pair);
}

void MainWindow::eraseMap()
{
    if(!m_map.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_map.contains(key.toStdString())){
        m_map.erase(key.toStdString());
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in set.\nChoose another key");
        return;
    }
}

void MainWindow::sizeMap()
{
    ui->InfoSet->clear();
    int size = m_map.size();
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("Size of map is " + s.setNum(size));
}

void MainWindow::emptyMap()
{
    ui->InfoSet->clear();
    if(m_map.empty()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Map is empty");
    }
    else{
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Map is not empty");
    }
}

void MainWindow::findMap()
{
    ui->InfoSet->clear();
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_map.contains(key.toStdString())){
         auto it = map<std::string,int>::BSTIterator(m_map.find(key.toStdString()));
         QString s;
         ui->InfoSet->setAlignment(Qt::AlignCenter);
         ui->InfoSet->setText("The key " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second) + " exists");
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in map.\nChoose another key");
        return;
    }
}

void MainWindow::containsMap()
{
    ui->InfoSet->clear();
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_map.contains(key.toStdString())){
        QString s;
        auto it = map<std::string,int>::BSTIterator(m_map.find(key.toStdString()));
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Map contains the key " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
    } else {
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Map doesn't contain the key " + key);
    }
}

void MainWindow::clearMap()
{
    ui->InfoSet->clear();
    if(!m_map.size()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Map is already empty");
    } else {
        m_map.clear();
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Size of map is " + s.setNum(m_map.size()));
    }
}

void MainWindow::beginMap()
{
    ui->InfoSet->clear();
    if(!m_map.size()){
        QMessageBox m;
        m.warning(this,"Error","Map is empty.\nAdd elements");
        return;
    }
    auto it = map<std::string,int>::BSTIterator(m_map.begin());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The first key of map is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
}

void MainWindow::backMap()
{
    ui->InfoSet->clear();
    if(!m_map.size()){
        QMessageBox m;
        m.warning(this,"Error","Map is empty.\nAdd elements");
        return;
    }
    auto it = map<std::string,int>::BSTIterator(m_map.back());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The last key of map is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
}

void MainWindow::lower_boundMap()
{
    ui->InfoSet->clear();
    if(!m_map.size()){
        QMessageBox m;
        m.warning(this,"Error","Map is empty.\nAdd elements");
        return;
    }
    ui->InfoSet->clear();
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    auto it = map<std::string,int>::BSTIterator(m_map.lower_bound(key.toStdString()));
    if(it != nullptr){
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("The first element not less than the given key is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
    } else {
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("There is no one element not less than the given key is");
    }
}

void MainWindow::upper_boundMap()
{
    ui->InfoSet->clear();
    if(!m_map.size()){
        QMessageBox m;
        m.warning(this,"Error","Map is empty.\nAdd elements");
        return;
    }
    ui->InfoSet->clear();
    QString key = ui->lineEdit_map->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    auto it = map<std::string,int>::BSTIterator(m_map.upper_bound(key.toStdString()));
    if(it != nullptr){
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("The first element greater than the given key is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
    } else {
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("There is no one element greater than the given key is");
    }
}

void MainWindow::print()
{
    ui->MainSet->clear();
    ui->MainSetValue->clear();
    m_map.printFirst();
    m_map.printSecond();
    ui->MainSet->setText(m_map.SF);
    ui->MainSetValue->setText(m_map.SS);
}

void MainWindow::on_do_map_clicked()
{
    int i = ui->comboBox_map->currentIndex();

    switch(i){
    case 0:
        insertMap();
        print();
        break;
    case 1:
        insert_or_assignMap();
        print();
        break;
    case 2:
        eraseMap();
        print();
        break;
    case 3:
        sizeMap();
        break;
    case 4:
        emptyMap();
        break;
    case 5:
        findMap();
        break;
    case 6:
        containsMap();
        break;
    case 7:
        clearMap();
        print();
        break;
    case 8:
        beginMap();
        break;
    case 9:
        backMap();
        break;
    case 10:
        lower_boundMap();
        break;
    case 11:
        upper_boundMap();
        break;
    }
}
