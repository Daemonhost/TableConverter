#ifndef SQLITELOADER_H
#define SQLITELOADER_H

#include <QSqlDatabase>
#include <QString>
#include "TableModel.h"

/*!
 * \brief Класс для чтения таблицы из базы данных SQLite.
 */
class SqliteReader
{
public:
    /*!
     * \param connectionName Имя соединения QSqlDatabase.
     */
    SqliteReader(const QString& connectionName);

    ~SqliteReader();

    /*!
     * \brief Открывает базу данных.
     *
     * Если во время открытия произошла ошибка, то error() вернет true, а
     * errorText() - сообщение об ошибке.
     */
    void open(const QString& fileName);

    /*!
     * \brief Считывает таблицу с данным именем из базы и делает из нее
     *        TableModel.
     * \param tableName Имя таблицы
     * \param parent Родитель новой TableModel
     *
     * В случае ошибки эта функция вернет nullptr, error() вернет
     * true, а errorText() - сообщение об ошибке.
     */
    TableModel* read(const QString& tableName, QObject* parent = nullptr);

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

    //! Возвращает базу данных, загруженную функцией load(const QString&).
    const QSqlDatabase& database() const;

private:
    bool mError;
    QString mErrorString;
    QSqlDatabase* mDatabase;
};

#endif // SQLITELOADER_H
