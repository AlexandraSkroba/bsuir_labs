#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "../../LR5/deque/deque.h"
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

private slots:
    void on_Open_clicked();

    void on_Close_clicked();

private:
    void push_back();
    void push_front();
    void pop_back();
    void pop_front();
    void DequeSize();
    void DequeEmpty();
    void clear();
    void resize();
    void DequeFront();
    void DequeBack();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    deque<int> deq;
};
#endif // MAINWINDOW_H
