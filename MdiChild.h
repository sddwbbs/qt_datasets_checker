#ifndef QT_HTTP_SERVICE_MDICHILD_H
#define QT_HTTP_SERVICE_MDICHILD_H

#include "DataModel.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QMetaObject>
#include <QMdiSubWindow>

class MdiChild : public QTableView {
Q_OBJECT

public:
    explicit MdiChild(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *event);

    bool loadFile(const QString &fileName);

    void initTable();

    QString currentFile() { return curFile; }

private slots:
    void onRowsInserted(const QModelIndex &, int, int);

    void onRowsRemoved(const QModelIndex &, int, int);

    void onDataChanged();

private:
    void setCurrentFile(const QString &fileName);

    QString userFriendlyCurrentFile();

    QString curFile;

    DataModel *tableModel;
};


#endif //QT_HTTP_SERVICE_MDICHILD_H
