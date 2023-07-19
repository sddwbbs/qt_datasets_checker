#ifndef QT_HTTP_SERVICE_REGISTRATION_H
#define QT_HTTP_SERVICE_REGISTRATION_H

#include <QDialog>
#include <QStatusBar>


QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration : public QDialog {
Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);

    ~Registration() override;

private slots:
    void create();

private:
    Ui::Registration *ui;
    QStatusBar *bar;
};


#endif //QT_HTTP_SERVICE_REGISTRATION_H
