#ifndef QT_HTTP_SERVICE_MAINWINDOW_H
#define QT_HTTP_SERVICE_MAINWINDOW_H

#include <QMainWindow>
#include "download.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void download();

private:
    Ui::MainWindow *ui;
    Download *downldWindow;
};

#endif //QT_HTTP_SERVICE_MAINWINDOW_H