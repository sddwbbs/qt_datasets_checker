#ifndef QT_HTTP_SERVICE_AUTHORIZATION_H
#define QT_HTTP_SERVICE_AUTHORIZATION_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Authorization; }
QT_END_NAMESPACE

class Authorization : public QDialog {
Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);

    ~Authorization() override;

private slots:
    void login();
    void createNewAcc();

private:
    Ui::Authorization *ui;
};


#endif //QT_HTTP_SERVICE_AUTHORIZATION_H
