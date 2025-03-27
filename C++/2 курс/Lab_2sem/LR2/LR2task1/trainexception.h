#ifndef TrainException_H
#define TrainException_H

#include <exception>
#include <QString>

class TrainException : public std::exception
{
private:
    QString message;
public:
    TrainException();
    TrainException(const QString& msg);
    QString getMessage() const;
};

#endif // TrainException_H
