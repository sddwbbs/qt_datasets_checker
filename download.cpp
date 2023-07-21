#include "download.h"
#include "ui_download.h"

#include <QUrl>
#include <QMessageBox>
#include <QPushButton>
#include <string>

Download::Download(QWidget *parent) :
        QDialog(parent), ui(new Ui::Download) {
    ui->setupUi(this);

    ui->webEngineView->setUrl(QUrl("https://www.kaggle.com/datasets/"));

    connect(ui->actionDownload, &QAction::triggered,
            this, &Download::download);

    // Добавляем кнопки "Назад" и "Вперед" и соединяем их с соответствующими обработчиками событий
    QPushButton *backButton = new QPushButton("Назад", this);
    QPushButton *forwardButton = new QPushButton("Вперед", this);

    connect(backButton, &QPushButton::clicked, this, &Download::goBack);
    connect(forwardButton, &QPushButton::clicked, this, &Download::goForward);

    // Помещаем кнопки в нужные позиции на форме
    ui->verticalLayout->addWidget(backButton);
    ui->verticalLayout->addWidget(forwardButton);

    // Соединяем сигнал urlChanged с соответствующим слотом
    connect(ui->webEngineView, &QWebEngineView::urlChanged,
            this, &Download::checkUrl);
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

    // Проверяем URL на условие
    if (url.toString().startsWith("https://www.kaggle.com/account/login?titleType=dataset-downloads")) {
        ui->webEngineView->setHtml("");
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "download", "Do you want to download this dataset?",
                                   QMessageBox::Ok | QMessageBox::Discard
                                   | QMessageBox::Cancel);
        if (ret == QMessageBox::Ok) {
            ui->webEngineView->back();
            ui->webEngineView->back();
            *temp = urlToDownload->toStdString();
            *temp = temp->substr(32, temp->length() - 1);
            //QMessageBox::warning(this, "URL", QString::fromStdString(*temp));
            std::string sysCall = "";
            sysCall = "cd /home/sdwbs/CLionProjects/qt_http_service && source myenv/bin/activate && kaggle datasets download " + *temp + " -p /home/sdwbs/CLionProjects/qt_http_service/Datasets/" + temp->substr(temp->find("/"), temp->length() - 1) + "/ --unzip";
            QMessageBox::warning(this, "URL", QString::fromStdString(sysCall));
            system(sysCall.c_str());
        } else {
            ui->webEngineView->back();
            ui->webEngineView->back();
        }
    }

}

//kaggle datasets download bhanupratapbiswas/uber-data-analysis -p /home/sdwbs/Downloads --unzip

