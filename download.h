#ifndef QT_HTTP_SERVICE_DOWNLOAD_H
#define QT_HTTP_SERVICE_DOWNLOAD_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Download; }
QT_END_NAMESPACE

class Download : public QDialog {
Q_OBJECT

public:
    explicit Download(QWidget *parent = nullptr);

    ~Download() override;

private slots:
    bool download();
    void goBack();
    void goForward();
    void checkUrl(const QUrl &url);

private:
    Ui::Download *ui;
    QString *urlToDownload = new(QString);
    std::string *temp = new(std::string);
};


#endif //QT_HTTP_SERVICE_DOWNLOAD_H
