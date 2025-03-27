#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include<string>

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
    void on_pushButtonLine_clicked();

private:
    Ui::MainWindow *ui;
    QString code;
    QString spare = "";
    std::string temp;

    std::vector<std::string> date1;
    std::vector<std::string> date2;
    std::vector<std::string> date3;
    std::vector<std::string> name;
};
#endif // MAINWINDOW_H
