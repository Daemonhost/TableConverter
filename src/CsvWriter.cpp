#include "CsvWriter.h"

#include <QFile>
#include <QTextStream>
#include <QVariant>

CsvWriter::CsvWriter() :
    mError(false),
    mErrorString() {}

void CsvWriter::write(const QString& fileName, const TableModel* model)
{
    // Экранирует двойные кавычки и ставит двойные кавычки в начале и в конце
    // строки
    auto escapeText = [](const QString& text) -> QString
    {
        QString escaped(text);
        // В CSV двойные кавычки экранируются не \", а ""
        escaped.replace("\"", "\"\"").prepend("\"").append("\"");
        return escaped;
    };

    QFile csvFile(fileName);
    if(!csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        mError = true;
        mErrorString = QString("Не удалось открыть файл %1: %2")
                       .arg(fileName, csvFile.errorString());
        return;
    }

    QTextStream csv(&csvFile);
    // Имена столбцов
    for(int j=0; j < model->columnCount(); ++j)
    {
        csv << escapeText(model->headerData(j, Qt::Horizontal, Qt::DisplayRole)
                          .toString());
        if(j < model->columnCount()-1)
            csv << ",";
    }
    csv << "\n";
    // Содержимое таблицы
    for(int i=0; i < model->rowCount(); ++i)
    {
        for(int j=0; j < model->columnCount(); ++j)
        {
            QVariant data = model->data(model->index(i,j),
                                        TableModel::Roles::AsIs);
            if(!data.isNull())
            {
                if(qstrcmp(data.typeName(), "QString") == 0)
                    csv << escapeText(data.toString());
                else
                    csv << data.toString();
            }
            if(j < model->columnCount()-1)
                csv << ",";
        }
        csv << "\n";
    }

    csvFile.close();
}

bool CsvWriter::error() const
{
    return mError;
}

const QString& CsvWriter::errorString() const
{
    return mErrorString;
}
