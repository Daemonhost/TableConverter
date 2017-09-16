#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QTextStream>
#include "SqliteLoader.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastFilePath = QDir::homePath();

    ui->tableView->setSelectionMode(QTableView::NoSelection);
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    connect(ui->fileOpenAction, &QAction::triggered,
            this, &MainWindow::fileOpen);
    connect(ui->fileSaveAsAction, &QAction::triggered,
            this, &MainWindow::fileSaveAs);
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
                       lastFilePath,
                       tr("SQLite (*.db)"));

    // Пользователь нажал "Отмена" или закрыл окно выбора файла
    if(fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);

    lastFilePath = fileInfo.absolutePath();

    // Расширение файла
    QString extension = fileInfo.suffix().toLower();

    if(extension == "db")
    {
        SqliteLoader sqliteLoader("OpenDbConnection");
        sqliteLoader.load(fileName);
        if(sqliteLoader.error())
        {
            QMessageBox::critical(this, tr("Ошибка"), sqliteLoader.errorString());
            return;
        }
        QStringList tables = sqliteLoader.database().tables();
        QString tableName;
        if(tables.size() == 0)
        {
            QMessageBox::critical(this, tr("Ошибка"),
                                  tr("Данная база SQLite не содержит таблиц"));
        }
        // Если таблица только одна, то загружаем ее
        else if(tables.size() == 1)
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
            QMessageBox::critical(this, tr("Ошибка"), sqliteLoader.errorString());
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

void MainWindow::fileSaveAs()
{
    if(ui->tableView->model() == nullptr
            || ui->tableView->model()->rowCount() == 0
            || ui->tableView->model()->columnCount() == 0)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Таблица пуста"));
        return;
    }

    // TODO Добавить возможность сохранения в SQLite
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),
                       lastFilePath,
                       tr("CSV (*.csv)"));

    // Пользователь нажал "Отмена" или закрыл окно выбора файла
    if(fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);

    lastFilePath = fileInfo.absolutePath();

    // Экранирует двойные кавычки и ставит двойные кавычки в начале и в конце
    // строки
    auto escapeText = [](const QString& text) -> QString
    {
        QString escaped(text);
        // В CSV двойные кавычки экранируются не \", а ""
        escaped.replace("\"", "\"\"").prepend("\"").append("\"");
        return escaped;
    };

    // Расширение файла
    QString extension = fileInfo.suffix().toLower();

    if(extension == "csv")
    {
        QFile csvFile(fileName);
        if(!csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(this, tr("Ошибка"),
                                  tr("Не удалось открыть файл: ")
                                  + csvFile.errorString());
            return;
        }

        const QAbstractItemModel* model = ui->tableView->model();
        QTextStream csv(&csvFile);
        // Имена столбцов
        for(int j=0; j < model->columnCount(); ++j)
        {
            csv << escapeText(model->headerData(j, Qt::Horizontal).toString());
            if(j < model->columnCount()-1)
                csv << ", ";
        }
        csv << "\n";
        // Содержимое таблицы
        for(int i=0; i < model->rowCount(); ++i)
        {
            for(int j=0; j < model->columnCount(); ++j)
            {
                QVariant data = model->data(model->index(i,j),
                                            TableModel::Roles::AsIs);
                if(data.isNull())
                    csv << "NULL";
                else if(qstrcmp(data.typeName(), "QString") == 0)
                    csv << escapeText(data.toString());
                else
                    csv << data.toString();
                if(j < model->columnCount()-1)
                    csv << ", ";
            }
            csv << "\n";
        }

        csvFile.close();
    }
    // TODO Добавить db
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
