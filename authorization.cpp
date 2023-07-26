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

    PGconn *conn = PQconnectdb("dbname=postgres user=postgres password=postgres host=db port=5432");

    if (PQstatus(conn) != CONNECTION_OK) {
        QApplication::restoreOverrideCursor();
        QMessageBox::warning(this, "db error", "error connecting to db");
        PQfinish(conn);
        return;
    }

    const char *selectSql = "SELECT username FROM accounts WHERE username = $1 AND password = $2";
    const char *selectParamValues[2] = {username.toStdString().c_str(), password.toStdString().c_str()};
    const int selectParamLengths[2] = {static_cast<int>(strlen(selectParamValues[0])),
                                       static_cast<int>(strlen(selectParamValues[1]))};
    const int selectParamFormats[2] = {0, 0};

    PGresult *selectResult = PQexecParams(conn, selectSql, 2, nullptr, selectParamValues, selectParamLengths, selectParamFormats, 0);

    if (PQresultStatus(selectResult) != PGRES_TUPLES_OK) {
        QApplication::restoreOverrideCursor();
        bar->showMessage("error while querying data", 2500);
        PQclear(selectResult);
        PQfinish(conn);
        return;
    }

    int numRows = PQntuples(selectResult);

    if (numRows == 0) {
        QApplication::restoreOverrideCursor();
        bar->showMessage("invalid username or password", 2500);
        PQclear(selectResult);
        PQfinish(conn);
        return;
    }

    bar->showMessage("successful authorization", 2500);

    QApplication::restoreOverrideCursor();
    PQclear(selectResult);
    PQfinish(conn);
    this->close();
    mainWindow = new MainWindow(this);
    mainWindow->show();
}

void Authorization::createNewAcc() {
    Registration regWindow(this);
    regWindow.exec();
}