#ifndef UTILITY_H
#define UTILITY_H

#include <QVector>
#include <QVariant>
#include <memory>
#include "TableModel.h"

std::unique_ptr<TableModel> createModelFrom(
    const QVector<QVariant>& header,
    const QVector<QVector<QVariant>>& data);

bool tableModelEquals(const TableModel& model1, const TableModel& model2);

#endif // UTILITY_H
