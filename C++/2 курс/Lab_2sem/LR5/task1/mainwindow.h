#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../LR5/queue/queue/queue.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include "application.h"

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
    void on_Do_clicked();

    void on_Task_clicked();

    void on_Close_clicked();

private:
    void push();
    void pop();
    void size();
    void empty();
    void front();
    void back();
    void emplace();
    void swap();

signals:
    void sendSignal();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Application *app;
    queue<int> q1;
    queue<int> q2;
};
#endif // MAINWINDOW_H
