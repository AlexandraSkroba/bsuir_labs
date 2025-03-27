#include "train.h"

const QString NOT_SPECIFIED = "NOT_SPECIFIED";

Train::Train()
    : _number_(NOT_SPECIFIED),
      _dest_date_(QDate()),
      _dest_time_(QTime()),
      _dest_point_(NOT_SPECIFIED),
      _free_seats_(0)
{}

Train::Train(const QString& num,const QDate &dest_date,const QTime &dest_time,const QString& dest_point, int free_seats = 0)
    : _number_(num), _dest_date_(dest_date),_dest_time_(dest_time),_dest_point_(dest_point),_free_seats_(free_seats)
{

}

QString Train::getNumber() {
    return this->_number_;
}
QDate Train::getDestDate() {
    return this->_dest_date_;
}
QTime Train::getDestTime() {
    return this->_dest_time_;
}
QString Train::getDestPoint() {
    return this->_dest_point_;
}
int Train::getFreeSeats() {
    return this->_free_seats_;
}

void Train::setNumber(const QString& num) {
    this->_number_ = num;
}
void Train::setDestDate(const QDate& date) {
    this->_dest_date_ = date;
}
void Train::setDestTime(const QTime& time) {
    this->_dest_time_ = time;
}
void Train::setDestPoint(const QString& point) {
    this->_dest_point_ = point;
}
void Train::setFreeSeats(int free_seats) {
    this->_free_seats_ = free_seats;
}
