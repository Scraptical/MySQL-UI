#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    db=QSqlDatabase::addDatabase("QMARIADB");
    db.setHostName("172.20.30.253");
    db.setDatabaseName("t.gutierez");
}

Widget::~Widget() {}
