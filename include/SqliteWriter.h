#ifndef SQLITEWRITER_H
#define SQLITEWRITER_H

#include <QAbstractItemModel>
#include <QString>
#include <QSqlDatabase>
#include "TableModel.h"

class SqliteWriter
{
public:
    SqliteWriter(const QString& connectionName);

    ~SqliteWriter();

    /*!
     * \brief Открывает базу данных.
     *
     * Если во время загрузки произошла ошибка, то error() вернет true, а
     * errorText() - сообщение об ошибке.
     */
    void open(const QString& fileName);

    void write(const QString& fileName, const TableModel* model);

    /*!
     * \brief Возвращает true, если во время предыдущих операций произошла
     *        ошибка. Иначе false.
     */
    bool error() const;

    /*!
     * \brief Возвращает текст последней ошибки, если она произошла, а иначе -
     *        пустую строку.
     */
    const QString& errorString() const;

    //! Возвращает базу данных, загруженную функцией open(const QString&).
    const QSqlDatabase& database() const;

private:
    bool mError;
    QString mErrorString;
    QSqlDatabase* mDatabase;
};

#endif // SQLITEWRITER_H
