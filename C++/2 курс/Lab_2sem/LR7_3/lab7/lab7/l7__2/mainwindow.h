#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hash_map.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mapInsert_clicked();

    void on_mapCount_clicked();

    void on_mapErase_clicked();

    void on_mapAt_clicked();

    void on_mapClear_clicked();

    void on_mapPrintAll_clicked();

    void on_mapSize_clicked();

private:
    hash_map<int, int> mp;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
