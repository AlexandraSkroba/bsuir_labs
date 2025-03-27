#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->schedule->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSchedule() {
    ui->schedule->setRowCount(trains.size());
    for (int i = 0; i < trains.size(); i++) {
            ui->schedule->setItem(i, 0, new QTableWidgetItem(trains.at(i).getNumber()));
            ui->schedule->setItem(i, 1, new QTableWidgetItem(trains.at(i).getDestDate().toString("dd.MM.yyyy")));
            ui->schedule->setItem(i, 2, new QTableWidgetItem(trains.at(i).getDestTime().toString("hh:mm")));
            ui->schedule->setItem(i, 3, new QTableWidgetItem(trains.at(i).getDestPoint()));
            ui->schedule->setItem(i, 4, new QTableWidgetItem(QString::number(trains.at(i).getFreeSeats())));
    }
}

void MainWindow::on_actionAdd_clicked()
{
    try {
        QString num = QInputDialog::getText(this, tr("Новый поезд"), tr("Введите номер поезда"), QLineEdit::Normal, "1");
        QDate date = QDate::fromString(QInputDialog::getText(this, tr("Новый поезд"), tr("Введите дату отправления поезда"), QLineEdit::Normal, "22.12.2018")
                                     , "dd.MM.yyyy");
        QTime time = QTime::fromString(QInputDialog::getText(this, tr("Новый поезд"), tr("Введите время отправления поезда"), QLineEdit::Normal, "22:36"),
                                       "hh:mm");
        QString dest = QInputDialog::getText(this, tr("Новый поезд"), tr("Введите точку прибытия поезда"), QLineEdit::Normal, "Minsk");
        std::cout << date.toString().toUtf8().constData() << std::endl;
        int free = QInputDialog::getInt(this, tr("Новый поезд"), tr("Введите кол-во свободных месь"), 10, 0, 100000000, 1);
        if (num == "" || dest == "" || !time.isValid()) {
            return;
        }
        trains.add_back(*new Train(num, date, time, dest, free));
        updateSchedule();
    } catch(...) {
        QMessageBox error;
        std::cout << "Error while adding" << std::endl;
        error.setText("Что-то пошло не так. Попробуйте ещё раз");
        error.exec();
        return;
    }
}



void MainWindow::on_actionFind_clicked()
{
    try {
        QString num = QInputDialog::getText(this, tr("Поиск поезда"), tr("Введите номер поезда"), QLineEdit::Normal, "1");
        for (int i = 0; i < trains.size(); i++) {
            if (trains.at(i).getNumber() == num) {
                QMessageBox callback(this);
                QString text = "";
                text += "Номер: " + trains.at(i).getNumber() + "\n";
                text += "Время отправления: " + trains.at(i).getDestDate().toString("dd.MM.yyyy") + " " + trains.at(i).getDestTime().toString("hh:mm") + "\n";
                text += "Свободных мест: " + QString::number(trains.at(i).getFreeSeats());
                callback.setText(text);
                callback.exec();
                return;
            }
        }
        throw new TrainException("Train not found");
    } catch (...) {
        QMessageBox callback(this);
        callback.setText("Поезд не найден");
        callback.exec();
    }

}

void MainWindow::on_actionFilter_clicked()
{

    QDate date = QDate::fromString(QInputDialog::getText(this, tr("Фильтр"), tr("Введите дату отправления поезда"), QLineEdit::Normal, "22.12.2018")
                                 , "dd.MM.yyyy");
    QTime time = QTime::fromString(QInputDialog::getText(this, tr("Фильтр"), tr("Введите время отправления поезда"), QLineEdit::Normal, "22:36"),
                                   "hh:mm");
    QString dest = QInputDialog::getText(this, tr("Новый поезд"), tr("Введите точку прибытия поезда"), QLineEdit::Normal, "Minsk");
    ui->schedule->setRowCount(0);
    for (int i = 0; i < trains.size(); i++) {
        if (
                trains.at(i).getDestPoint() == dest &&
                trains.at(i).getDestTime() <= time &&
                trains.at(i).getDestDate() <= date
                ) {
            ui->schedule->setRowCount(ui->schedule->rowCount() + 1);
            ui->schedule->setItem(ui->schedule->rowCount() - 1, 0, new QTableWidgetItem(trains.at(i).getNumber()));
            ui->schedule->setItem(ui->schedule->rowCount() - 1, 1, new QTableWidgetItem(trains.at(i).getDestDate().toString("dd.MM.yyyy")));
            ui->schedule->setItem(ui->schedule->rowCount() - 1, 2, new QTableWidgetItem(trains.at(i).getDestTime().toString("hh:mm")));
            ui->schedule->setItem(ui->schedule->rowCount() - 1, 3, new QTableWidgetItem(trains.at(i).getDestPoint()));
            ui->schedule->setItem(ui->schedule->rowCount() - 1, 4, new QTableWidgetItem(QString::number(trains.at(i).getFreeSeats())));
        }
    }

}

void MainWindow::on_actionClear_clicked()
{
    updateSchedule();
}

void MainWindow::on_actionBook_clicked()
{
    try {
        QString num = QInputDialog::getText(this, tr("Бронирование"), tr("Введите номер поезда"), QLineEdit::Normal, "1");
        for (int i = 0; i < trains.size(); i++) {
            if (trains.at(i).getNumber() == num) {
                bool ok = true;
                int seats = QInputDialog::getInt(this, tr("Бронирование"), tr("Введите количество мест"), 1, 1, trains.at(i).getFreeSeats(), 1, &ok);
                if (ok && seats <= trains.at(i).getFreeSeats()) {
                    trains.at(i).setFreeSeats(trains.at(i).getFreeSeats() - seats);
                    updateSchedule();
                    throw new TrainException("Бронирование успешно");
                } else {
                    throw new TrainException("Недостаточно мест");
                }
            }
        }
        throw new TrainException("Поезд не найден");
    } catch(TrainException* e) {
        QMessageBox callback(this);
        callback.setText(e->getMessage());
        callback.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(0,"Выберите файл","","*.txt");

    if(filePath.isEmpty()){
        ui->label->setText("Вы ничего не открыли");
        return;
    }


    QFile file(filePath);
    QTextStream stream(&file);

    if(!file.open(QIODevice::ReadWrite)){
        ui->label->setText("Не получаеться открыть этот файл");
        return;
    }

    if(file.size() == 0){
        ui->label->setText("Вы открыли пустой файл");
        return;
    }

    List<Train> listTmp;

    while(!stream.atEnd()){
        auto tmp = stream.readLine().split(' ');

        if(tmp.length() != 5 || !QDate::fromString(tmp.at(0),Qt::DateFormat::ISODate).isValid() ||
                !QTime::fromString(tmp.at(1),Qt::DateFormat::ISODate).isValid() ||
                tmp.at(2).length() > 21 || tmp.at(2).length() < 0 ||
                tmp.at(3).toInt() > 10000 || tmp.at(3).toInt() < 0 ||
                tmp.at(4).toInt() > 1000 || tmp.at(4).toInt() < 0)
        {
            ui->label->setText("Некоректные данные в файле");
            return;
        }    // проверка на корректность введённых даннных

        listTmp.add_back(*new Train(tmp.at(2),
                                    QDate::fromString(tmp.at(0),Qt::DateFormat::ISODate),
                                    QTime::fromString(tmp.at(1),Qt::DateFormat::ISODate),
                                    tmp.at(3),
                                    tmp.at(4).toInt()));

    }
        file.close();
        trains =listTmp;
        updateSchedule();

}
