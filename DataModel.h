#ifndef QT_HTTP_SERVICE_DATAMODEL_H
#define QT_HTTP_SERVICE_DATAMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <vector>

class DataModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QList<QStringList> dataset;
    int columns;

public:
    explicit DataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    const void setColumns(int col);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    const QList<QStringList> &getData();

    bool insertRow(int position, const QStringList &value);

    bool removeRow(const int position);

    int howManyRecords();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
};


#endif //QT_HTTP_SERVICE_DATAMODEL_H
