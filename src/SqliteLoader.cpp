#include "SqliteLoader.h"

#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

SqliteLoader::SqliteLoader(const QString& connectionName) :
    mError(false),
    mErrorText(),
    mDatabase(QSqlDatabase::addDatabase("QSQLITE", connectionName)) {}

void SqliteLoader::load(const QString& fileName)
{
    mDatabase.setDatabaseName(fileName);
    if(!mDatabase.open())
    {
        mError = true;
        mErrorText = QString("Не удалось открыть файл: ")
                     + mDatabase.lastError().text();
    }
}

TableModel* SqliteLoader::tableModel(const QString& tableName, QObject* parent)
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("SELECT * FROM %1").arg(tableName));
    if(!query.exec())
    {
        mError = true;
        mErrorText = QString("Не удалось открыть таблицу: ")
                     + query.lastError().text();
        return nullptr;
    }
    else
    {
        TableModel* model = new TableModel(parent);
        QSqlRecord record = query.record();
        // SQLite не поддерживает query.size()
        query.last();
        int rowCount = query.at() + 1;
        query.first();
        int columnCount = record.count();
        model->resize(rowCount, columnCount);
        for(int j=0; j < columnCount; ++j)
            model->setHeaderData(j, record.field(j).name());

        for(int i=0; i < rowCount; ++i)
        {
            for(int j=0; j < columnCount; ++j)
                model->setData(i, j, query.value(j));
            query.next();
        }

        return model;
    }
}

bool SqliteLoader::error() const
{
    return mError;
}

const QString& SqliteLoader::errorString() const
{
    return mErrorText;
}

const QSqlDatabase& SqliteLoader::database() const
{
    return mDatabase;
}
