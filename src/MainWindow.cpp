#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "SqliteLoader.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastFileOpenPath = QDir::homePath();

    ui->tableView->setSelectionMode(QTableView::NoSelection);
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    connect(ui->fileOpenAction, &QAction::triggered,
            this, &MainWindow::fileOpen);
    connect(ui->fileQuitAction, &QAction::triggered,
            this, &MainWindow::fileQuit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
    // TODO Добавить возможность загрузки CSV
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                       lastFileOpenPath,
                       tr("SQLite (*.db)"));

    // Пользователь нажал "Отмена" или закрыл окно выбора файла
    if(fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);

    lastFileOpenPath = fileInfo.absolutePath();

    // Расширение файла
    QString extension = fileInfo.suffix();

    if(extension == "db")
    {
        SqliteLoader sqliteLoader("OpenDbConnection");
        sqliteLoader.load(fileName);
        if(sqliteLoader.error())
        {
            QMessageBox::critical(this, tr("Ошибка"), sqliteLoader.errorText());
            return;
        }
        QStringList tables = sqliteLoader.database().tables();
        QString tableName;
        // Если таблица только одна, то загружаем ее
        if(tables.size() == 1)
            tableName = tables.first();
        // Иначе, спрашиваем пользователя, какую таблицу загрузить
        else
        {
            // TODO Реализовать выбор
            tableName = tables.first();
        }

        TableModel* model = sqliteLoader.tableModel(tableName, ui->tableView);
        if(sqliteLoader.error())
        {
            QMessageBox::critical(this, tr("Ошибка"), sqliteLoader.errorText());
            return;
        }
        ui->tableView->setModel(model);
    }
    // TODO Добавить CSV
    else
    {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Неизвестное расширение файла: \"")
                              + extension + "\"");
    }
}

void MainWindow::fileQuit()
{
    QApplication::quit();
}
