#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "unordered_map.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void insertUMap();
    void insert_or_assignUMap();
    void eraseUMap();
    void sizeUMap();
    void max_sizeUMap();
    void emptyUMap();
    void findUMap();
    void containsUMap();
    void clearUMap();
    void rehashUMap();
    void reserveUMap();
    void beginUMap();
    void backUMap();

    void print();

private slots:
    void on_do_Umap_clicked();

private:
    Ui::MainWindow *ui;
    unordered_map<std::string,int> m_Umap;
};
#endif // MAINWINDOW_H
