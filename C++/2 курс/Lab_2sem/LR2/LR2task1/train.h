#ifndef TRAIN_H
#define TRAIN_H

#include <QString>
#include <QDate>
#include <QTime>

class Train {
private:
    QString _number_;
    QDate _dest_date_;
    QTime _dest_time_;
    QString _dest_point_;
    int _free_seats_;

public:
    Train();
    Train(const QString& num,const QDate &dest_date,const QTime &dest_time,const QString& dest_point, int free);

    QString getNumber();
    QDate getDestDate();
    QTime getDestTime();
    QString getDestPoint();
    int getFreeSeats();

    void setNumber(const QString& num);
    void setDestDate(const QDate& date);
    void setDestTime(const QTime& time);
    void setDestPoint(const QString& point);
    void setFreeSeats(int free_seats);
};

#endif // TRAIN_H
