#include "utility.h"

using namespace std;

unique_ptr<TableModel> createModelFrom(
    const QVector<QVariant>& header,
    const QVector<QVector<QVariant>>& data)
{
    // У QAbstractItemModel нет конструктора перемещения, поэтому используем
    // unique_ptr
    unique_ptr<TableModel> model(new TableModel);
    model->setColumnCount(header.size());
    model->setRowCount(data.size());
    for(int j=0; j < model->columnCount(); ++j)
        model->setHeaderData(j, header[j]);

    for(int i=0; i < model->rowCount(); ++i)
        for(int j=0; j < model->columnCount(); ++j)
            model->setData(i, j, data[i][j]);

    return model;
}

bool tableModelEquals(const TableModel& model1, const TableModel& model2)
{
    if(model1.columnCount() != model2.columnCount()
            || model1.rowCount() != model2.rowCount())
        return false;

    for(int j=0; j < model1.columnCount(); ++j)
        if(model1.headerData(j) != model2.headerData(j))
            return false;

    for(int i=0; i < model1.rowCount(); ++i)
        for(int j=0; j < model1.columnCount(); ++j)
            if(model1.data(i,j) != model2.data(i,j))
                return false;

    return true;
}
