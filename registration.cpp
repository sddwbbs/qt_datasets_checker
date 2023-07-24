#include <iostream>
#include "registration.h"
#include "ui_registration.h"
#include <QAction>
#include <QString>
#include <QMessageBox>

Registration::Registration(QWidget *parent) :
        QDialog(parent), ui(new Ui::Registration) {
    ui->setupUi(this);
    bar = new QStatusBar(this);
    ui->formLayout->addWidget(bar);

    resize(700, 400);

//    connect(ui->actionCreate, &QAction::triggered,
//            this, &Registration::create);

    PGconn *conn = connectToDB();

    if (conn) {
        bar->showMessage("Stable connection", 1500);
        // Выполняйте здесь ваши операции с базой данных, используя conn
        PQfinish(conn); // Закрываем соединение после использования
    } else {
        bar->showMessage("Error connecting to the database", 1500);
    }
}

PGconn* Registration::connectToDB() {
    const char *conninfo = "dbname=user_accounts user=postgres password=postgres hostaddr=172.21.0.2 port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    // Проверяем состояние подключения
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return nullptr;
    }

    return conn;
}

//#include <QSqlDatabase>
//#include <QtSql>
//
//#include <libpq-fe.h>
//
//#include "registration.h"
//#include "ui_registration.h"
//#include <QAction>
//#include <QString>
//#include <QMessageBox>
//
//Registration::Registration(QWidget *parent) :
//        QDialog(parent), ui(new Ui::Registration) {
//    ui->setupUi(this);
//    bar = new QStatusBar(this);
//    ui->formLayout->addWidget(bar);
//
//    resize(700, 400);
//
//    connect(ui->actionCreate, &QAction::triggered,
//            this, &Registration::create);
//
//    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//
////    db.setPassword("postgres");
////    db.setDatabaseName("user_accounts");
////    db.setUserName("postgres");
//
//    db.setHostName("localhost"); // Замените на имя хоста или IP-адрес контейнера с PostgreSQL
//    db.setPort(5432); // Укажите порт, на котором запущен PostgreSQL в контейнере (по умолчанию 5432)
//    db.setDatabaseName("user_accounts"); // Укажите имя базы данных
//    db.setUserName("postgres"); // Укажите имя пользователя базы данных
//    db.setPassword("postgres"); // Укажите пароль для пользователя базы данных
//
//    if (!db.open()) {
//        bar->showMessage("error connecting to db klfjalkf", 1500);
//    } else {
//        bar->showMessage("stable connection 14134", 1500);
//    }
//}

Registration::~Registration() {
    delete ui;
}

//void Registration::create() {
//    QString username = ui->UsernameLedit->text();
//    QString password = ui->PasswordLedit->password();
//    QString confirmPassword = ui->ConfirmPasswordLedit->password();
//
//    QSqlQuery selectQuery;
//    selectQuery.prepare("SELECT username FROM accounts WHERE username = ?");
//    selectQuery.addBindValue(username);
//
//    if (!selectQuery.exec()) {
//        bar->showMessage("error while querying data", 2500);
//        return;
//    }
//
//    if (selectQuery.next()) {
//        bar->showMessage("username already exists", 2500);
//        return;
//    }
//
//    if (confirmPassword != password) {
//        bar->showMessage("passwords must match", 2500);
//        return;
//    }
//
//    // Здесь можно создать нового пользователя
//    QSqlQuery insertQuery;
//    insertQuery.prepare("INSERT INTO accounts (username, password) VALUES (?, ?)");
//    insertQuery.addBindValue(username);
//    insertQuery.addBindValue(password);
//
//    if (!insertQuery.exec()) {
//        bar->showMessage("error while inserting data");
//        return;
//    }
//
//    QMessageBox::warning(this, "registration", "registration successful");
//}
