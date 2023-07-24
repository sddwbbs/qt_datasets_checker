#include "MdiChild.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

MdiChild::MdiChild(QWidget *parent):
        QTableView(parent)
        , tableModel(new DataModel(this))
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    connect(tableModel, &QAbstractTableModel::dataChanged, this, &MdiChild::onDataChanged);
    connect(tableModel, &QAbstractTableModel::rowsInserted, this, &MdiChild::onRowsInserted);
    connect(tableModel, &QAbstractTableModel::rowsRemoved, this, &MdiChild::onRowsRemoved);

    setWindowTitle(userFriendlyCurrentFile());
    this->setSortingEnabled(true);
}

void MdiChild::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
}

void MdiChild::onRowsInserted(const QModelIndex &, int, int) {

}

void MdiChild::onRowsRemoved(const QModelIndex &, int, int) {

}

void MdiChild::onDataChanged() {

}

void MdiChild::setCurrentFile(const QString &fileName) {

}

QString MdiChild::userFriendlyCurrentFile() {
    return QString();
}

bool MdiChild::loadFile(const QString &fileName) {
    setCurrentFile(fileName);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                                     .arg(fileName)
                                     .arg(file.errorString()));
        return false;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    QTextStream in(&file);
    int row = tableModel->rowCount();

    QStringList headers = in.readLine().split(",");
    tableModel->setColumns(headers.length());

    std::list<std::string> stdStringList;
    for (const QString& qString : headers) {
        stdStringList.push_back(qString.toStdString());
    }

    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(",");

        tableModel->insertRow(row, fields);
        ++row;
    }

    initTable();
    file.close();

    QApplication::restoreOverrideCursor();

    // Ставим контекстное меню для ячеек
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    this->setModel(tableModel);

    return true;
}

void MdiChild::initTable() {
    QList<QStringList> dataset = tableModel->getData();

    for (int row = 0; row < tableModel->rowCount(); ++row) {
        for (int column = 0; column < tableModel->columnCount(); ++column) {
            tableModel->setData(tableModel->index(row, column), dataset[row][column]);
        }
    }
}
