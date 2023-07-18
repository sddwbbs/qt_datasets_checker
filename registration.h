//
// Created by sdwbs on 18.07.23.
//

#ifndef QT_HTTP_SERVICE_REGISTRATION_H
#define QT_HTTP_SERVICE_REGISTRATION_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration : public QDialog {
Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);

    ~Registration() override;

private slots:
    bool create();

private:
    Ui::Registration *ui;
};


#endif //QT_HTTP_SERVICE_REGISTRATION_H
