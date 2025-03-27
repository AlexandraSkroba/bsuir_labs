#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "map.h"

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
    void insertMap();
    void insert_or_assignMap();
    void eraseMap();
    void sizeMap();
    void emptyMap();
    void findMap();
    void containsMap();
    void clearMap();
    void beginMap();
    void backMap();
    void lower_boundMap();
    void upper_boundMap();

    void print();

private slots:
    void on_do_map_clicked();

private:
    Ui::MainWindow *ui;
    map<std::string,int> m_map;
};
#endif // MAINWINDOW_H
