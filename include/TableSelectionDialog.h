#ifndef TABLESELECTIONDIALOG_H
#define TABLESELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TableSelectionDialog;
}

/*!
 * \brief Окно для выбора имени таблицы для чтения/записи в SQLite
 */
class TableSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    //! Создает \p TableSelectionDialog с данным родителем
    explicit TableSelectionDialog(QWidget* parent = 0);

    ~TableSelectionDialog();

    //! Меняет содержимое и параметр \p editable у \p ui->tableName
    void setTableNames(const QStringList& names, bool editable);

    //! Возвращает индекс выбранного элемента у \p ui->tableName
    int currentNameIndex() const;

    //! Возвращает текст \p ui->tableName
    QString currentName() const;

private:
    Ui::TableSelectionDialog *ui;
};

#endif // TABLESELECTIONDIALOG_H
