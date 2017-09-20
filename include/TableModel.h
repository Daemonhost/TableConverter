#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

/*!
 * \brief Хранит таблицу для отображения в QTableView
 */
class TableModel : public QAbstractTableModel
{
public:
    /*!
     * \brief Роли для data(const QModelIndex&, int) и
     *        headerData(int, Qt::Orientation, int)
     */
    enum Roles : int
    {
        //! Возвращать данные как они есть
        AsIs = Qt::UserRole
    };

    TableModel(QObject* parent = nullptr);

    //! Количество строк
    inline int rowCount() const
    {
        return mData.size();
    }

    //! Количество строк (функция для вызова из view)
    int rowCount(const QModelIndex& parent) const override;

    /*!
     * \brief Меняет количество строк на \p rowCount
     *
     * Если количество строк меньше предыдущего, то лишние данные
     * удаляются. Если больше, то создаются пустые ячейки.
     */
    void setRowCount(int rowCount);

    //! Добавляет строку в конец таблицы, заполненную пустыми \p QVariant
    void appendRow();

    //! Количество столбцов
    inline int columnCount() const
    {
        return mHeaderData.size();
    }

    //! Количество столбцов (функция для вызова из view)
    int columnCount(const QModelIndex& parent) const override;

    /*!
     * \brief Меняет количество столбцов на \p columnCount
     *
     * Если количество столбцов меньше предыдущего, то лишние данные
     * удаляются. Если больше, то создаются пустые ячейки.
     */
    void setColumnCount(int columnCount);

    /*!
     * \brief Возвращает содержимое ячейки (\p row, \p column)
     *
     * Эта функция не проверяет выход индексов за пределы таблицы.
     */
    inline QVariant data(int row, int column) const
    {
        return mData[row][column];
    }

    /*!
     * \brief Изменяет содержимое ячейки (\p row, \p column)
     *
     * Эта функция не проверяет выход индексов за пределы таблицы.
     */
    inline void setData(int row, int column, const QVariant& value)
    {
        mData[row][column] = value;
    }

    /*!
     * \brief Возвращает содержимое ячейки по индексу \p index
     *        (функция для вызова из view)
     *
     * Эта функция не проверяет выход индексов за пределы таблицы.
     */
    QVariant data(const QModelIndex& index, int role) const override;

    /*!
     * \brief Изменяет имя стобца номер \p column
     *
     * Эта функция не проверяет выход индекса за пределы таблицы.
     */
    inline void setHeaderData(int column, const QVariant& value)
    {
        mHeaderData[column] = value;
    }

    /*!
     * \brief Возвращает имя стобца номер \p column
     *
     * Эта функция не проверяет выход индекса за пределы таблицы.
     */
    inline QVariant headerData(int column) const
    {
        return mHeaderData[column];
    }

    /*!
     * \brief Возвращает имя стобца номер \p section
     *        (функция для вызова из view)
     *
     * Эта функция не проверяет выход индекса за пределы таблицы.
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    /*!
     * \brief Изменяет размер таблицы на \p rowCount строк и \p columnCount
     *        столбцов.
     *
     * Если количество строк или столбцов меньше предыдущего, то лишние данные
     * удаляются. Если больше, то создаются пустые ячейки.
     */
    void resize(int rowCount, int columnCount);

private:
    //! Имена столбцов таблицы
    QVector<QVariant> mHeaderData;

    //! Содержимое таблицы
    QVector<QVector<QVariant>> mData;
};

#endif // TABLEMODEL_H
