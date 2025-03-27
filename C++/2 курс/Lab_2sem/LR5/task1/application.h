#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "../../LR5/queue/queue/queue.h"

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_FullFill_clicked();

    void on_Open_clicked();

    void on_Close_clicked();

private:
    Ui::Application *ui;
    QGraphicsScene *scene;
    queue<int> mainQ;
    queue<int> subQ1;
    queue<int> subQ2;
};

#endif // APPLICATION_H
