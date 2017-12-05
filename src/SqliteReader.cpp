#include "SqliteReader.h"

#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

SqliteReader::SqliteReader(const QString& connectionName) :
    mError(false),
    mErrorString(),
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",
                               connectionName))) {}

SqliteReader::~SqliteReader()
{
    QString connectionName = mDatabase->connectionName();
    mDatabase->close();
    delete mDatabase;
    QSqlDatabase::removeDatabase(connectionName);
}

void SqliteReader::open(const QString& fileName)
{
    mDatabase->setDatabaseName(fileName);
    if(!mDatabase->open())
    {
        mError = true;
        mErrorString = QString("Не удалось открыть файл: ")
                       + mDatabase->lastError().text();
    }
}

TableModel* SqliteReader::read(const QString& tableName, QObject* parent)
{
    QSqlQuery query(*mDatabase);
    if(!query.exec(QString("SELECT * FROM %1").arg(tableName)))
    {
        mError = true;
        mErrorString = QString("Не удалось открыть таблицу: ")
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

bool SqliteReader::error() const
{
    return mError;
}

const QString& SqliteReader::errorString() const
{
    return mErrorString;
}

const QSqlDatabase& SqliteReader::database() const
{
    return *mDatabase;
}
