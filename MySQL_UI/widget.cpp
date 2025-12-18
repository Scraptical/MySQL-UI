#include "widget.h"
#include <mariadb/conncpp.hpp>
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bLog = new QPushButton("Login",this);
    bQuitter = new QPushButton("Quitter",this);
    Connection = new QLabel(this);
    Result = new QLabel(this);
    ID = new QLineEdit(this);
    ID -> setPlaceholderText("Entrez votre identifiant");
    mdp = new QLineEdit(this);
    mdp -> setPlaceholderText("Entrez votre mot de passe");

    QHBoxLayout *BLayout = new QHBoxLayout;
    QVBoxLayout *LineLayout = new QVBoxLayout;
    QVBoxLayout *MainLayout = new QVBoxLayout;

    BLayout -> addWidget(bLog);
    BLayout -> addWidget(bQuitter);
    BLayout -> addWidget(Connection);
    LineLayout -> addWidget(ID);
    LineLayout -> addWidget(mdp);
    LineLayout -> addWidget(Result);

    MainLayout -> addLayout(LineLayout);
    MainLayout -> addLayout(BLayout);

    setLayout(MainLayout);

    connect(bLog,SIGNAL(clicked()),this,SLOT(Login()));
    connect(bQuitter,SIGNAL(clicked()),this,SLOT(close()));
}

void Widget::Login()
{
    QString PassW = mdp -> text();
    QString User = ID -> text();

    try
    {
        //Connexion à la base
        sql::Driver* driver;
        sql::Connection* conn;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://172.20.30.253:3306/t.gutierrez");
        sql::Properties properties({{"user", "t.gutierrez"}, {"password", "t.gutierrez"}});
        conn = driver->connect(url, properties);

        if (conn)
        {
            //Connection -> setText("Connexion MariaDB réussie!");
        }
        std::cout<<"user:"<<User.toStdString()<<" mdp : "<<PassW.toStdString()<<std::endl;
        pstmt = conn->prepareStatement("SELECT COUNT(*) as res FROM Logins WHERE identifiant=? AND mdp=?");
        pstmt->setString(1, User.toStdString());
        pstmt->setString(2, PassW.toStdString());

        res = pstmt->executeQuery();
        if(res->first()){
       if (res -> getInt("res") == 1)
        {
           QMessageBox::information(this,"Succès","Connexion Réussit");
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Votre identifiant et/ou mot de passe est incorrect");
        }
        }
        delete res;
        delete pstmt;
        delete conn;
    }
    catch (sql::SQLException &e)
    {
        Connection -> setText(e.what());
    }
}

Widget::~Widget() {}
