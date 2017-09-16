#ifndef SQLITELOADER_H
#define SQLITELOADER_H

#include <QSqlDatabase>
#include <QString>
#include "TableModel.h"

/*!
 * \brief Класс для загрузки таблицы из базы данных SQLite и возможностью
 *        отображения таблиц в QTableView.
 */
class SqliteLoader
{
public:
    /*!
     * \param connectionName Имя соединения QSqlDatabase.
     */
    SqliteLoader(const QString& connectionName);

    /*!
     * \brief Загружает базу данных из файла.
     *
     * Если во время загрузки произошла ошибка, то error() вернет true, а
     * errorText() - сообщение об ошибке.
     */
    void load(const QString& fileName);

    /*!
     * \brief Считывает таблицу с данным именем из базы и делает из нее
     *        TableModel.
     * \param tableName Имя таблицы
     * \param parent Родитель новой TableModel
     *
     * В случае ошибки эта функция вернет nullptr, error() вернет
     * true, а errorText() - сообщение об ошибке.
     */
    TableModel* tableModel(const QString& tableName, QObject* parent = nullptr);

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
    QString mErrorText;
    QSqlDatabase mDatabase;
};

#endif // SQLITELOADER_H
