#include "TableSelectionDialog.h"
#include "ui_TableSelectionDialog.h"

TableSelectionDialog::TableSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableSelectionDialog)
{
    ui->setupUi(this);
}

TableSelectionDialog::~TableSelectionDialog()
{
    delete ui;
}

void TableSelectionDialog::setTableNames(const QStringList& names,
        bool editable)
{
    ui->tableName->setEditable(editable);
    ui->tableName->clear();
    ui->tableName->addItems(names);
}

int TableSelectionDialog::currentNameIndex() const
{
    return ui->tableName->currentIndex();
}
