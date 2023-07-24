#include "DataModel.h"

DataModel::DataModel(QObject *parent):
        QAbstractTableModel(parent)
{

}

int DataModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : dataset.count();
}

int DataModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : columns;
}

QVariant DataModel::data(const QModelIndex &index, int role) const {
    // Работать имеет смысл только при корректном индексе
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();

    int row = index.row();
    int col = index.column();

    // Определяем, с какой ролью был вызван метод "data()", и что он должен
    // теперь сделать с ячейкой
    switch (role) {
        // Роль, которая отрабатывает, если ячейка отображается в таблице
        case Qt::DisplayRole :

            // Роль, которая отрабатывает при редактировании ячейки таблицы
        case Qt::EditRole :
            return dataset[row][col];

            // Роль для изменения фона ячейки
        case Qt::BackgroundRole :
            // Для всех остальных случаев выдать недопустимый вариант (invalid)
            return QVariant();

            // Для всех остальных случаев выдать недопустимый вариант (invalid)
        default:
            return QVariant();
    }

    // Для всех остальных случаев выдать недопустимый вариант (invalid)
    return QVariant();
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    // Проверим на корректность "index"
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return false;

    // Определяем текущий столбец
    int row = index.row();
    int col = index.column();

    // Определяем текущую роль. Тут почти всегда будет "EditRole".
    // Другие роли будут, если поменяется поле ввода с текстовой на "QCheckBox"
    if (role == Qt::EditRole) {
        dataset[row][col] = value.toString();
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        // Если всё хорошо, то вызывающему методу сообщаем об этом
        return true;
    }

    // Если вставить данные не удалось
    return false;
}

const QList<QStringList> &DataModel::getData() {
    //return reinterpret_cast<QList<std::vector<QString>> &>(dataset);
    return dataset;
}

bool DataModel::insertRow(int position, const QStringList &value) {
    beginInsertRows(QModelIndex(), position, position);
    dataset.insert(position, value);
    //numberOfRecords++;
    endInsertRows();
    return true;
}

bool DataModel::removeRow(const int position) {
    /*
    if (numberOfRecords == 0) {
        return false;
    }*/

    beginRemoveRows(QModelIndex(), position, position);
    dataset.removeAt(position);
    //numberOfRecords--;
    endRemoveRows();
    return true;
}

int DataModel::howManyRecords() {
    return 0;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Задаём заголовки для столбцов при их отображении
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        // Определяем какой сейчас столбец. Отсчёт идёт от нуля
        switch (section) {
//            case 0: return QString(tr("ID"));
//            case 1: return QString(tr("Name"));
//            case 2: return QString(tr("Number of Employees"));
//            case 3: return QString(tr("Workload"));
//            case 4: return QString(tr("Location"));
//            case 5: return QString(tr("Additional Services"));
//            case 6: return QString(tr("Price"));
//            case 7: return QString(tr("Experience"));
//            case 8: return QString(tr("Completed Projects"));
//            case 9: return QString(tr("Rating"));
        }
    }

    // Задаём заголовки для строк при их отображении
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        // Поскольку строки просто нумеруются, можно просто передать значение
        // "section + 1" и преобразовать его из "int" в "QString"
        return QString::number(section + 1);

    // Для всех остальных случаев выдать недопустимый вариант (invalid)
    return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() != 0)
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column);
}

const void DataModel::setColumns(int col) {
    this->columns = col;
}
