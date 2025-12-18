#include "widget.h"
#include <mariadb/conncpp.hpp>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bLog = new QPushButton("Login",this);
    bQuitter = new QPushButton("Quitter",this);
    Connection = new QLabel(this);
    ID = new QLineEdit("Entrez votre identifiant",this);
    mdp = new QLineEdit("Entrez votre mot de passe",this);

    QHBoxLayout *BLayout = new QHBoxLayout;
    QVBoxLayout *LineLayout = new QVBoxLayout;
    QVBoxLayout *MainLayout = new QVBoxLayout;

    BLayout -> addWidget(bLog);
    BLayout -> addWidget(bQuitter);
    BLayout -> addWidget(Connection);
    LineLayout -> addWidget(ID);
    LineLayout -> addWidget(mdp);

    MainLayout -> addLayout(LineLayout);
    MainLayout -> addLayout(BLayout);

    setLayout(MainLayout);

    connect(bLog,SIGNAL(clicked()),this,SLOT(Login()));
    connect(bQuitter,SIGNAL(clicked()),this,SLOT(close()));
}

void Widget::Login()
{
    try
    {
        //Connexion à la base
        sql::Driver* driver;
        sql::Connection* conn;
        driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://172.20.30.253:3306/t.gutierrez");
        sql::Properties properties({{"user", "t.gutierrez"}, {"password", "t.gutierrez"}});
        conn = driver->connect(url, properties);
        if (conn)
        {
            Connection -> setText("Connexion MariaDB réussie!");
        }
        delete conn;
    }
    catch (sql::SQLException &e)
    {
        Connection -> setText(e.what());
    }
}

Widget::~Widget() {}
