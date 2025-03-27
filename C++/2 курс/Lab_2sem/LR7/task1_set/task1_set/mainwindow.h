#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set.h"
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
    void insertSet();
    void eraseSet();
    void sizeSet();
    void emptySet();
    void findSet();
    void containsSet();
    void clearSet();
    void beginSet();
    void backSet();
    void emplaceSet();
    void lower_boundSet();
    void upper_boundSet();

    void print();

private slots:
    void on_do_set_clicked();

private:
    Ui::MainWindow *ui;
    set<int> m_set;
};
#endif // MAINWINDOW_H
