#include <QSqlDatabase>
#include <QtSql>

#include "authorization.h"
#include "ui_authorization.h"
#include <QAction>
#include <QString>
#include <QMessageBox>

#include "registration.h"
#include "mainwindow.h"

Authorization::Authorization(QWidget *parent) :
        QDialog(parent), ui(new Ui::Authorization) {
    ui->setupUi(this);
    bar = new QStatusBar(this);
    ui->formLayout->addWidget(bar);

    resize(600, 350);

    connect(ui->actionLogin, &QAction::triggered,
            this, &Authorization::login);
    connect(ui->actionCreateNewAcc, &QAction::triggered,
            this, &Authorization::createNewAcc);
}

Authorization::~Authorization() {
    delete ui;
}

void Authorization::login() {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString username = ui->UsernameLedit->text();
    QString password = ui->PasswordLedit->password();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("user_accounts");
    db.setUserName("postgres");

    if (!db.open()) {
        QApplication::restoreOverrideCursor();
        QMessageBox::warning(this, "db error", "error connecting to db");
        return;
    }

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT username FROM accounts WHERE username = ? AND password = ?");
    selectQuery.addBindValue(username);
    selectQuery.addBindValue(password);

    if (!selectQuery.exec()) {
        QApplication::restoreOverrideCursor();
        bar->showMessage("error while querying data", 2500);
        return;
    }

    if (!selectQuery.next()) {
        QApplication::restoreOverrideCursor();
        bar->showMessage("invalid username or password", 2500);
        return;
    }

    bar->showMessage("successful authorization", 2500);

    QApplication::restoreOverrideCursor();
    db.close();
    this->close();
    mainWindow = new MainWindow(this);
    mainWindow->show();
}

void Authorization::createNewAcc() {
    Registration regWindow(this);
    regWindow.exec();
}