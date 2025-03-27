#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <QTextStream>
#include <QHeaderView>
#include <QFileDialog>

#include <iostream>

#include "list.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateSchedule();

private slots:
    void on_actionAdd_clicked();

    void on_actionFind_clicked();

    void on_actionFilter_clicked();

    void on_actionClear_clicked();

    void on_actionBook_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    List<Train> trains;
    QString filePath = "";

};

#endif // MAINWINDOW_H
