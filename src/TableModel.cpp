#include "TableModel.h"

TableModel::TableModel(QObject* parent) :
    QAbstractTableModel(parent) {}

int TableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return rowCount();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return columnCount();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();
    else
        return data(index.row(), index.column());
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if(role != Qt::DisplayRole)
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
