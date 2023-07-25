#include "download.h"
#include "ui_download.h"

#include <QUrl>
#include <QMessageBox>
#include <string>

Download::Download(QWidget *parent) :
        QDialog(parent), ui(new Ui::Download) {
    ui->setupUi(this);

    ui->webEngineView->setUrl(QUrl("https://www.kaggle.com/datasets/"));

    connect(ui->actionDownload, &QAction::triggered,
            this, &Download::download);

    connect(ui->actionBack, &QAction::triggered, this, &Download::goBack);
    connect(ui->actionForward, &QAction::triggered, this, &Download::goForward);

    // Соединяем сигнал urlChanged с соответствующим слотом
    connect(ui->webEngineView, &QWebEngineView::urlChanged,
            this, &Download::checkUrl);

    this->setWindowFlags(Qt::Window);
    resize(1800, 1100);
}

Download::~Download() {
    delete ui;
}

bool Download::download() {
    QUrl currentUrl = ui->webEngineView->url();
    QString str = currentUrl.toString();
    QMessageBox::warning(this, "URL", str);

    return true;
}

void Download::goBack() {
    ui->webEngineView->back();
}

void Download::goForward() {
    ui->webEngineView->forward();
}

void Download::checkUrl(const QUrl &url) {
    if (url.toString().startsWith("https://www.kaggle.com/datasets/")) {
        *urlToDownload = url.toString();
    }

    if (url.toString().startsWith("https://www.kaggle.com/account/login?titleType=dataset-downloads")) {
        ui->webEngineView->setHtml("");
        QMessageBox::StandardButton ret;
        ret = QMessageBox::question(this, "download", "Do you want to download this dataset?",
                                   QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            ui->webEngineView->back();
            ui->webEngineView->back();
            *temp = urlToDownload->toStdString();
            *temp = temp->substr(32, temp->length() - 1);
            std::string sysCall = "";
            sysCall = "cd /app/Datasets && source myenv/bin/activate && kaggle datasets download " + *temp + " -p /home/sdwbs/CLionProjects/qt_http_service/Datasets/" + temp->substr(temp->find("/"), temp->length() - 1) + "/ --unzip";
            QMessageBox::warning(this, "URL", QString::fromStdString(sysCall));
            system(sysCall.c_str());
        } else {
            ui->webEngineView->back();
            ui->webEngineView->back();
        }
    }
}
