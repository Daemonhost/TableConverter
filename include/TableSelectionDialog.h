#ifndef TABLESELECTIONDIALOG_H
#define TABLESELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TableSelectionDialog;
}

class TableSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableSelectionDialog(QWidget *parent = 0);
    ~TableSelectionDialog();

    void setTableNames(const QStringList& names, bool editable);
    int currentNameIndex() const;

private:
    Ui::TableSelectionDialog *ui;
};

#endif // TABLESELECTIONDIALOG_H
