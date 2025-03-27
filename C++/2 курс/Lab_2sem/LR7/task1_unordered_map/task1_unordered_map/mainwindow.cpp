#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(361,255);

    ui->comboBox_Umap->addItems(QStringList() << " insert " << " insert_or_assing " << " erase " << " size " << " max_size " << " empty " << " find " << " contains " << " clear " << " rehash " << " reserve "  << " begin " << " back ");

    ui->spinBox_Umap->setAlignment(Qt::AlignCenter);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << " Hash " << " Key " << " Data ");
    ui->tableWidget->setColumnWidth(0,108);
    ui->tableWidget->setColumnWidth(1,108);
    ui->tableWidget->setColumnWidth(2,108);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertUMap()
{
    QString key = ui->lineEdit_Umap->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    int data = ui->spinBox_Umap->value();
    if(m_Umap.contains(key.toStdString())){
        QMessageBox m;
        m.warning(this,"Error","UMap already has such key.\nAdd another key");
        return;
    }
    pair<std::string,int> m_pair;
    m_pair.first = key.toStdString();
    m_pair.second = data;
    m_Umap.insert(m_pair);
}

void MainWindow::insert_or_assignUMap()
{
    QString key = ui->lineEdit_Umap->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    int data = ui->spinBox_Umap->value();
    pair<std::string,int> m_pair;
    m_pair.first = key.toStdString();
    m_pair.second = data;
    m_Umap.insert_or_assign(m_pair);
}

void MainWindow::eraseUMap()
{
    if(!m_Umap.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    QString key = ui->lineEdit_Umap->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_Umap.contains(key.toStdString())){
        m_Umap.erase(key.toStdString());
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in UMap.\nChoose another key");
        return;
    }
}

void MainWindow::sizeUMap()
{
    ui->InfoSet->clear();
    int size = m_Umap.size();
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("Size of UMap is " + s.setNum(size));
}

void MainWindow::max_sizeUMap()
{
    ui->InfoSet->clear();
    int max_size = m_Umap.max_size();
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("Size of UMap is " + s.setNum(max_size));
}

void MainWindow::emptyUMap()
{
    ui->InfoSet->clear();
    if(m_Umap.empty()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("UMap is empty");
    }
    else{
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("UMap is not empty");
    }
}

void MainWindow::findUMap()
{
    ui->InfoSet->clear();
    QString key = ui->lineEdit_Umap->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_Umap.contains(key.toStdString())){
         auto it = unordered_map<std::string,int>::Iterator(m_Umap.find(key.toStdString()));
         QString s;
         ui->InfoSet->setAlignment(Qt::AlignCenter);
         ui->InfoSet->setText("The key " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second) + " exists");
    } else {
        QMessageBox m;
        m.warning(this,"Error","There is no sush key in UMap.\nChoose another key");
        return;
    }
}

void MainWindow::containsUMap()
{
    ui->InfoSet->clear();
    QString key = ui->lineEdit_Umap->text();
    if(key==""){
        QMessageBox m;
        m.warning(this,"Error","Input key.\nPlease do it");
        return;
    }
    if(m_Umap.contains(key.toStdString())){
        QString s;
        auto it = unordered_map<std::string,int>::Iterator(m_Umap.find(key.toStdString()));
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("UMap contains the key " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
    } else {
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("UMap doesn't contain the key " + key);
    }
}

void MainWindow::clearUMap()
{
    ui->InfoSet->clear();
    if(!m_Umap.size()){
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("UMap is already empty");
    } else {
        m_Umap.clear();
        QString s;
        ui->InfoSet->setAlignment(Qt::AlignCenter);
        ui->InfoSet->setText("Size of UMap is " + s.setNum(m_Umap.size()));
    }
}

void MainWindow::rehashUMap()
{
    if(!m_Umap.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    m_Umap.rehash();
}

void MainWindow::reserveUMap()
{
    if(!m_Umap.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    m_Umap.reserve();
}

void MainWindow::beginUMap()
{
    ui->InfoSet->clear();
    if(!m_Umap.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    auto it = unordered_map<std::string,int>::Iterator(m_Umap.begin());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The first key of UMap is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));
}

void MainWindow::backUMap()
{
    ui->InfoSet->clear();
    if(!m_Umap.size()){
        QMessageBox m;
        m.warning(this,"Error","UMap is empty.\nAdd elements");
        return;
    }
    auto it = unordered_map<std::string,int>::Iterator(m_Umap.back());
    QString s;
    ui->InfoSet->setAlignment(Qt::AlignCenter);
    ui->InfoSet->setText("The last key of UMap is " + QString::fromStdString((*it).first) + " with data " + s.setNum((*it).second));

}

void MainWindow::print()
{
    ui->tableWidget->setRowCount(0);
    if(!m_Umap.size())
        return;
    int k = m_Umap.size();
    int rows = 0;
    auto it = unordered_map<std::string,int>::Iterator(m_Umap.begin());
    for(int i = 0;i<k;i++){
        ui->tableWidget->setRowCount(rows+1);
        QString hash, data;
        ui->tableWidget->setItem(rows,0, new QTableWidgetItem(hash.setNum(it.getHash())));
        ui->tableWidget->setItem(rows,1, new QTableWidgetItem(QString::fromStdString((*it).first)));
        ui->tableWidget->setItem(rows,2, new QTableWidgetItem(hash.setNum((*it).second)));
        rows++;
        if(i != k-1)
            it++;
    }
}

void MainWindow::on_do_Umap_clicked()
{
    int i = ui->comboBox_Umap->currentIndex();

    switch(i){
    case 0:
        insertUMap();
        print();
        break;
    case 1:
        insert_or_assignUMap();
        print();
        break;
    case 2:
        eraseUMap();
        print();
        break;
    case 3:
        sizeUMap();
        break;
    case 4:
        max_sizeUMap();
        break;
    case 5:
        emptyUMap();
        break;
    case 6:
        findUMap();
        break;
    case 7:
        containsUMap();
        break;
    case 8:
        clearUMap();
        print();
        break;
    case 9:
        rehashUMap();
        print();
        break;
    case 10:
        reserveUMap();
        print();
        break;
    case 11:
        beginUMap();
        break;
    case 12:
        backUMap();
        break;
    }
}
