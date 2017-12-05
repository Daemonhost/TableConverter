#include "SqliteWriter.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

    SqliteWriter::SqliteWriter(const QString& connectionName):
        mError(false),
        mErrorString(),
        mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",
                                   connectionName))) {}
    SqliteWriter::~SqliteWriter()
    {
        QString connectionName = mDatabase->connectionName();
        mDatabase->close();
        delete mDatabase;
        QSqlDatabase::removeDatabase(connectionName);
    }

    void SqliteWriter::open(const QString& fileName)
    {
        mDatabase->setDatabaseName(fileName);
        if(!mDatabase->open())
        {
            mError = true;
            mErrorString = QString("Не удалось открыть файл: ")
                           + mDatabase->lastError().text();
        }
    }

    void SqliteWriter::write(const QString& tableName, const TableModel *model)
    {
        if(!mDatabase->transaction())
        {
            mError = true;
            mErrorString = mDatabase->lastError().text();
            return;
        }

        QSqlQuery query(*mDatabase);
        if(!query.exec(QString("DROP TABLE IF EXISTS %1").arg(tableName)))
        {
            mError = true;
            mErrorString = query.lastError().text();
            query.clear();
            mDatabase->rollback();
            return;
        }

        // Сюда будет записываться команда SQL
        // Команда создания таблицы имеет вид:
        // CREATE TABLE name(col1 int, col2 real, col3 text)
        QString sqlCommand = QString("CREATE TABLE %1(")
                             .arg(QString(tableName));

        for(int j=0; j < model->columnCount(); ++j)
        {
            sqlCommand += model->headerData(j).toString();
            if(model->data(0,j).type() == QVariant::Type::Int)
                sqlCommand += " int";
            else if(model->data(0,j).type() == QVariant::Type::Double)
                sqlCommand += " real";
            else
                sqlCommand += " text";
            if(j < model->columnCount() - 1)
                sqlCommand += ", ";
        }
        sqlCommand += ")";

        if(!query.exec(sqlCommand))
        {
            mError = true;
            mErrorString = query.lastError().text();
            query.clear();
            mDatabase->rollback();
            return;
        }

        query.clear();
        sqlCommand = QString("INSERT INTO %1 VALUES(").arg(QString(tableName));
        for(int j=0; j < model->columnCount(); ++j)
        {
            sqlCommand += "?";
            if(j < model->columnCount() - 1)
                sqlCommand += ", ";
        }
        sqlCommand += ")";

        if(!query.prepare(sqlCommand))
        {
            mError = true;
            mErrorString = query.lastError().text();
            query.clear();
            mDatabase->rollback();
            return;
        }

        for(int i=0; i < model->rowCount(); ++i)
        {
            for(int j=0; j < model->columnCount(); ++j)
            {
                query.bindValue(j, model->data(i,j));
            }

            if(!query.exec())
            {
                mError = true;
                mErrorString = query.lastError().text();
                query.clear();
                mDatabase->rollback();
                return;
            }
        }

        if(!mDatabase->commit())
        {
            mError = true;
            mErrorString = mDatabase->lastError().text();
            return;
        }
    }

    bool SqliteWriter::error() const
    {
        return mError;
    }

    const QString& SqliteWriter::errorString() const
    {
        return mErrorString;
    }

    const QSqlDatabase& SqliteWriter::database() const
    {
        return *mDatabase;
    }

