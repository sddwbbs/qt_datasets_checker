#include <QSqlDatabase>
#include <QtSql>

#include "registration.h"
#include "ui_registration.h"
#include <QAction>
#include <QString>
#include <QMessageBox>

Registration::Registration(QWidget *parent) :
        QDialog(parent), ui(new Ui::Registration) {
    ui->setupUi(this);

    resize(700, 400);

    connect(ui->actionCreate, &QAction::triggered,
            this, &Registration::create);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("user_accounts");
    db.setUserName("postgres");

    if (!db.open()) {
        QMessageBox::warning(0, "db error", db.lastError().text());
    } else {
        QMessageBox::information(0, "ok", "connected with db");
    }
}

Registration::~Registration() {
    delete ui;
}

bool Registration::create() {
    QString username = ui->Username->text();
    QString password = ui->Password->text();

    QSqlQuery query;
    query.exec("create table test (id integer primary key, adaf varchar(10))");
}
