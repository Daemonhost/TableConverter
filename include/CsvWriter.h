#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <QString>
#include "TableModel.h"

/*!
 * \brief Класс для записи таблицы в csv.
 */
class CsvWriter
{
public:
    CsvWriter();

    /*!
     * \brief Записывает \p model в CSV файл.
     * \param fileName Имя файла
     * \param model Таблица
     *
     * В случае ошибки error() вернет true, а errorText() - сообщение об ошибке.
     */
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

private:
    bool mError;
    QString mErrorString;
};

#endif // CSVWRITER_H
