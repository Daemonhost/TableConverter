#ifndef SQLITEWRITER_H
#define SQLITEWRITER_H

#include <QAbstractItemModel>
#include <QString>
#include <QSqlDatabase>
#include "TableModel.h"

/*!
 * \brief Класс для записи таблицы в базу данных SQLite.
 */
class SqliteWriter
{
public:
    /*!
     * \brief Создает \p SqliteWriter и открывает соединение с базой данных
     * \param connectionName Имя соединения
     */
    SqliteWriter(const QString& connectionName);

    ~SqliteWriter();

    /*!
     * \brief Открывает базу данных.
     *
     * Если во время открытия произошла ошибка, то error() вернет true, а
     * errorText() - сообщение об ошибке.
     */
    void open(const QString& fileName);

    /*!
     * \brief Записывает \p model в раннее открытую базу данных.
     *        Если таблица уже существует, то она пересоздается.
     * \param tableName Имя таблицы
     * \param model Таблица
     */
    void write(const QString& tableName, const TableModel* model);

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
