#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <mariadb/conncpp.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bLog = new QPushButton("Login",this);
    bQuitter = new QPushButton("Quitter",this);
    Connection = new QLabel(this);

    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout -> addWidget(bLog);
    hLayout -> addWidget(bQuitter);
    setLayout(hLayout);

    connect(bLog,SIGNAL(clicked()),this,SLOT(Login()));
    connect(bQuitter,SIGNAL(clicked()),this,SLOT(close()));
}

void MainWindow::Login()
{
    try
    {
        //Connexion à la base
        sql::Driver* driver;
        sql::Connection* conn;
        driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://172.20.30.253:3306/ma_bdd");
        sql::Properties properties({{"user", "mon_login"}, {"t.gutierrez", "t.gutierrez"}});
        conn = driver->connect(url, properties);
        if (conn)
        {
            Connection -> setText("Connexion MariaDB réussie!");
        }
        delete conn;
    }
    catch (sql::SQLException &e)
    {
        Connection -> setText("Erreur MariaDB");
        Connection -> setText("Code erreur");
        Connection -> setText("État SQL");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
