#ifndef QT_HTTP_SERVICE_MAINWINDOW_H
#define QT_HTTP_SERVICE_MAINWINDOW_H

#include <QMainWindow>
#include "download.h"
#include "MdiChild.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MdiChild;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void download();

    void open();

    MdiChild *createMdiChild();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    Download *downldWindow;

    MdiChild *activeMdiChild();

    QMdiSubWindow *findMdiChild(const QString &fileName);
};

#endif //QT_HTTP_SERVICE_MAINWINDOW_H