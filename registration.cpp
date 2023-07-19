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
    bar = new QStatusBar(this);
    ui->formLayout->addWidget(bar);

    resize(700, 400);

    connect(ui->actionCreate, &QAction::triggered,
            this, &Registration::create);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("user_accounts");
    db.setUserName("postgres");

    if (!db.open()) {
        bar->showMessage("error connecting to db", 1500);
    } else {
        bar->showMessage("stable connection", 1500);
    }
}

Registration::~Registration() {
    delete ui;
}

void Registration::create() {
    QString username = ui->UsernameLedit->text();
    QString password = ui->PasswordLedit->password();
    QString confirmPassword = ui->ConfirmPasswordLedit->password();

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT username FROM accounts WHERE username = ?");
    selectQuery.addBindValue(username);

    if (!selectQuery.exec()) {
        bar->showMessage("error while querying data");
        return;
    }

    if (selectQuery.next()) {
        bar->showMessage("username already exists", 2500);
        return;
    }

    if (confirmPassword != password) {
        bar->showMessage("passwords must match", 2500);
        return;
    }

    // Здесь можно создать нового пользователя
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO accounts (username, password) VALUES (?, ?)");
    insertQuery.addBindValue(username);
    insertQuery.addBindValue(password);

    if (!insertQuery.exec()) {
        bar->showMessage("error while inserting data");
        return;
    }

    QMessageBox::warning(this, "registration", "registration successful");
}
