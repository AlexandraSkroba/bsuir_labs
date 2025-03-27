#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bitset.h"

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

    void on_size_clicked();

    void on_any_clicked();

    void on_all_clicked();

    void on_count_clicked();

    void on_to_ullong_clicked();

    void on_to_ulong_clicked();

    void on_set_clicked();

    void on_flip_clicked();

    void on_none_clicked();

    void on_reset_clicked();

    void on_flip_all_clicked();

    void on_reset_all_clicked();

    void on_set_all_clicked();

    void on_test_clicked();

private:
    Ui::MainWindow *ui;
    static const size_t numberOfBits = 8;
    bitset<numberOfBits> bts;

    void update_bitset();
};
#endif // MAINWINDOW_H
