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

    connect(ui->actionCreate, &QAction::triggered,
            this, &Registration::create);

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
    const char *conninfo = "dbname=postgres user=postgres password=postgres host=db port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    // Проверяем состояние подключения
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return nullptr;
    }

    return conn;
}


Registration::~Registration() {
    delete ui;
}

void Registration::create() {
    QString username = ui->UsernameLedit->text();
    QString password = ui->PasswordLedit->password();
    QString confirmPassword = ui->ConfirmPasswordLedit->password();

    PGconn *conn = PQconnectdb("dbname=postgres user=postgres password=postgres host=db port=5432");

    if (PQstatus(conn) != CONNECTION_OK) {
        bar->showMessage("Error connecting to the database");
        PQfinish(conn);
        return;
    }

    const char *selectSql = "SELECT username FROM accounts WHERE username = $1";
    const char *selectParamValues[1] = {username.toStdString().c_str()};
    const int selectParamLengths[1] = {static_cast<int>(strlen(selectParamValues[0]))};
    const int selectParamFormats[1] = {0};

    PGresult *selectResult = PQexecParams(conn, selectSql, 1, nullptr, selectParamValues, selectParamLengths, selectParamFormats, 0);

    if (PQresultStatus(selectResult) != PGRES_TUPLES_OK) {
        bar->showMessage("Error while selecting data");
        PQclear(selectResult);
        PQfinish(conn);
        return;
    }

    int numRows = PQntuples(selectResult);

    if (numRows > 0) {
        bar->showMessage("Username already exists", 2500);
        PQclear(selectResult);
        PQfinish(conn);
        return;
    }

    PQclear(selectResult);

    if (confirmPassword != password) {
        bar->showMessage("Passwords must match", 2500);
        PQfinish(conn);
        return;
    }

    const char *insertSql = "INSERT INTO accounts (username, password) VALUES ($1, $2)";
    const char *insertParamValues[2] = {username.toStdString().c_str(), password.toStdString().c_str()};
    const int insertParamLengths[2] = {static_cast<int>(strlen(insertParamValues[0])),
                                       static_cast<int>(strlen(insertParamValues[1]))};
    const int insertParamFormats[2] = {0, 0};

    PGresult *insertResult = PQexecParams(conn, insertSql, 2, nullptr, insertParamValues, insertParamLengths, insertParamFormats, 0);

    if (PQresultStatus(insertResult) != PGRES_COMMAND_OK) {
        bar->showMessage("Error while inserting data");
        PQclear(insertResult);
        PQfinish(conn);
        return;
    }

    PQclear(insertResult);
    PQfinish(conn);

    QMessageBox::warning(this, "Registration", "Registration successful");
}