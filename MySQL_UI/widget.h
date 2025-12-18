#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton *bLog;
    QPushButton *bQuitter;
    QLabel *Connection;
    QLabel *Result;
    QLineEdit *ID;
    QLineEdit *mdp;

private slots :
    void Login();

};
#endif // WIDGET_H
