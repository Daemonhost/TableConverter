#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <QFile>
#include <QString>
#include "TableModel.h"

class CsvLoader
{
public:
    CsvLoader();

    /*!
     * \brief Считывает CSV файл с данным именем и делает из него
     *        TableModel.
     * \param fileName Имя файла
     * \param parent Родитель новой TableModel
     *
     * В случае ошибки эта функция вернет nullptr, error() вернет
     * true, а errorText() - сообщение об ошибке.
     */
    TableModel* read(const QString& fileName, QObject* parent = nullptr);

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
    //! Статус функции readElement
    enum class ReadElementStatus
    {
        //! Строка продолжается
        RowContinues,

        //! Строка кончилась
        RowEnded,

        //! Файл кончился
        FileEnded
    };

    /*!
     * \brief Метод, считывающий один элемент из CSV.
     * \return ReadElementStatus::RowContinues, если после элемента идет ','
     *         и ReadElementStatus::RowEnded, если после элемента идет '\n'.
     */
    ReadElementStatus readElement(QString& result, QFile& csvFile);

    /*!
     * \brief Выводит типы столбцов таблицы и приводит столбцы к выведенным
     *        типам.
     */
    void inferAndCastColumnTypes(TableModel* tableModel);

    enum class ElementType
    {
        Null,
        Int,
        Real,
        Text
    };

    /*!
     * \brief Выводит тип \p element и присваивает \p currentType ближайший
     *        общий тип \p element и \p currentType.
     */
    void updateColumnType(const QString& element, ElementType& currentType);

    bool mError;
    QString mErrorString;
};

#endif // CSVLOADER_H
