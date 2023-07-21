#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect (ui->actionDownload, &QAction::triggered,
             this, &MainWindow::download);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::download() {
    downldWindow = new Download(this);
   downldWindow->exec();
}