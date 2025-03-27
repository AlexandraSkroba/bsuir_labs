#include "trainexception.h"

TrainException::TrainException()
{

}

TrainException::TrainException(const QString& msg) {
    message = msg;
}
QString TrainException::getMessage() const {
    return message;
}
