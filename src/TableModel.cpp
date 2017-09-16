#include "TableModel.h"

TableModel::TableModel(QObject* parent) :
    QAbstractTableModel(parent) {}

int TableModel::rowCount(const QModelIndex& parent) const
{
    // Согласно документации Qt rowCount должен возвращать 0, если parent
    // валиден.
    if(parent.isValid())
        return 0;
    else
        return rowCount();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    // Согласно документации Qt columnCount должен возвращать 0, если parent
    // валиден.
    if(parent.isValid())
        return 0;
    else
        return columnCount();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if(role == Roles::AsIs)
        return data(index.row(), index.column());
    else if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant v = data(index.row(), index.column());
        if(v.isNull())
            return "NULL";
        else
            return v;
    }
    else
        return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if(role != Qt::DisplayRole && role != Roles::AsIs)
        return QVariant();
    // Имена столбцов
    else if(orientation == Qt::Horizontal)
        return headerData(section);
    // Номера строк
    else
        return section + 1;
}

void TableModel::resize(int rowCount, int columnCount)
{
    mData.resize(rowCount);
    if(columnCount != this->columnCount())
    {
        mHeaderData.resize(columnCount);
        for(int i=0; i < rowCount; ++i)
            mData[i].resize(columnCount);
    }
}
