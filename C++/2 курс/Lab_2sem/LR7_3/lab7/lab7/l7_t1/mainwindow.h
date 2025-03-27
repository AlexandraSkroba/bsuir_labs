#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map.h"
#include "set.h"

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
    void on_setCount_clicked();

    void on_setInsert_clicked();

    void on_setErase_clicked();

    void on_setClear_clicked();

    void on_setPrint_clicked();

    void on_setSize_clicked();

    void on_mapCount_clicked();

    void on_mapInsert_clicked();

    void on_mapErase_clicked();

    void on_mapAt_clicked();

    void on_mapClear_clicked();

    void on_mapPrintAll_clicked();

    void on_mapSize_clicked();

private:
    Ui::MainWindow *ui;
    set<int> s;
    map<int, int> mp;
};
#endif // MAINWINDOW_H
