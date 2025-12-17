#ifndef WIDGET_H
#define WIDGET_H

#include <QSqlDatabase>
#include <QWidget>
#include <QtSql>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QSqlDatabase db;
};
#endif // WIDGET_H
