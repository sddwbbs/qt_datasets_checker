#include "authorization.h"
#include "ui_authorization.h"
#include <QAction>
#include <QString>

#include "registration.h"

Authorization::Authorization(QWidget *parent) :
        QDialog(parent), ui(new Ui::Authorization) {
    ui->setupUi(this);

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
    QString username = ui->UsernameLedit->text();
    QString password = ui->PasswordLedit->password();
    close();
}

void Authorization::createNewAcc() {
    Registration regWindow(this);
    regWindow.exec();
}