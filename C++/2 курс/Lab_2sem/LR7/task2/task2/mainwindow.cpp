#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox->setRange(0, numberOfBits - 1);

    update_bitset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_bitset() {
    ui->bitset->setText(QString::fromStdString(bts.to_string()));
}

void MainWindow::on_any_clicked()
{
    QMessageBox::information(this, "Any", bts.any() ? "true" : "false");
}

void MainWindow::on_size_clicked()
{
    QMessageBox::information(this, "Size", QString::number(bts.size()));
}

void MainWindow::on_all_clicked()
{
    QMessageBox::information(this, "All", bts.all() ? "true" : "false");
}

void MainWindow::on_count_clicked()
{
    QMessageBox::information(this, "Count", QString::number(bts.count()));
}

void MainWindow::on_to_ullong_clicked()
{
    QMessageBox::information(this, "To_ullong", QString::number(bts.to_ullong()));
}


void MainWindow::on_to_ulong_clicked()
{
    QMessageBox::information(this, "To_ulong", QString::number(bts.to_ulong()));
}


void MainWindow::on_set_clicked()
{
    bts.set(ui->spinBox->value());
    update_bitset();
}


void MainWindow::on_flip_clicked()
{
    bts.flip(ui->spinBox->value());
    update_bitset();
}


void MainWindow::on_none_clicked()
{
    QMessageBox::information(this, "None", bts.none() ? "true" : "false");
}


void MainWindow::on_reset_clicked()
{
    bts.reset(ui->spinBox->value());
    update_bitset();
}


void MainWindow::on_flip_all_clicked()
{
    bts.flip();
    update_bitset();
}


void MainWindow::on_reset_all_clicked()
{
    bts.reset();
    update_bitset();
}


void MainWindow::on_set_all_clicked()
{
    bts.set();
    update_bitset();
}

void MainWindow::on_test_clicked()
{
    QMessageBox::information(this, "Test", bts.test(ui->spinBox->value()) ? "true" : "false");
}

