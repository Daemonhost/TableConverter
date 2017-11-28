#include "CsvLoader.h"

#include <QString>
#include <QVariant>
#include <QVector>

CsvLoader::CsvLoader() :
    mError(false),
    mErrorString() {}

TableModel* CsvLoader::read(const QString& fileName, QObject* parent)
{
    //Открытие csv и внесение данных в buffer
    QFile csvFile(fileName);
    if(!csvFile.open(QFile::ReadOnly | QFile::Text))
    {
        mError = true;
        mErrorString = csvFile.errorString();
        return nullptr;
    }

    QVector<QString> header;
    QString element;
    // Считываем заголовок
    ReadElementStatus status = readElement(element, csvFile);
    if(status == ReadElementStatus::FileEnded)
    {
        mError = true;
        mErrorString = QObject::tr("CSV файл пуст");
        csvFile.close();
        return nullptr;
    }
    header += element;
    while(status == ReadElementStatus::RowContinues)
    {
        status = readElement(element, csvFile);
        header += element;
    }

    TableModel* tableModel = new TableModel(parent);
    tableModel->setColumnCount(header.size());
    for(int i=0; i < header.size(); ++i)
        tableModel->setHeaderData(i, header[i]);
    header.clear();

    //Вложенный цикл, заполняющий заголовок и ячейки таблицы данными из файла
    while(status != ReadElementStatus::FileEnded)
    {
        for (int j = 0; j < tableModel->columnCount(); j++)
        {
            status = readElement(element, csvFile);
            if(error())
            {
                delete tableModel;
                csvFile.close();
                return nullptr;
            }
            else if(status == ReadElementStatus::FileEnded && j == 0)
            {
                break;
            }
            else if(status == ReadElementStatus::RowContinues
                    && j == tableModel->columnCount() - 1)
            {
                mError = true;
                mErrorString = QObject::tr("В строке ");
                mErrorString += QString::number(tableModel->rowCount());
                mErrorString += " больше столбцов, чем нужно";
                delete tableModel;
                csvFile.close();
                return nullptr;
            }
            else if(status != ReadElementStatus::RowContinues
                    && j != tableModel->columnCount() - 1)
            {
                mError = true;
                mErrorString = QObject::tr("В строке ");
                mErrorString += QString::number(tableModel->rowCount());
                mErrorString += " меньше столбцов, чем нужно";
                delete tableModel;
                csvFile.close();
                return nullptr;
            }
            else
            {
                if(j == 0)
                {
                    tableModel->appendRow();
                }
                tableModel->setData(tableModel->rowCount()-1, j,
                                    QVariant(element));
            }
        }
    }

    csvFile.close();
    return tableModel;
}

CsvLoader::ReadElementStatus CsvLoader::readElement(QString& result,
                                                    QFile& csvFile)
{
    char ch; //Переменная для поочередной записи символов
    result.clear();

    while(csvFile.getChar(&ch) && (ch == ' ' || ch == '\t'));
    if(csvFile.atEnd())
        return ReadElementStatus::FileEnded;
    else if(ch == ',')
        return ReadElementStatus::RowContinues;
    else if(ch == '\n')
        return ReadElementStatus::RowEnded;

    if (ch != '"') // Кавычек нет
    {
        result += ch;
        while(csvFile.getChar(&ch) && ch != '\n' && ch != ',')
        {
            result += ch;
        }
        result = result.trimmed();
        if(ch == ',')
            return ReadElementStatus::RowContinues;
        else
            return ReadElementStatus::RowEnded;
    }
    else // Кавычки есть
    {
        while(csvFile.getChar(&ch))
        {
            if(ch == '"')
            {
                csvFile.peek(&ch, 1);
                if(ch == '"')
                {
                    result += '"';
                    csvFile.getChar(&ch);
                }
                else
                    break;
            }
            else
                result += ch;
        }

        if(csvFile.atEnd() && ch != '"')
        {
            mError = true;
            mErrorString = QObject::tr("В CSV не закрыта кавычка");
            return ReadElementStatus::RowContinues;
        }

        while(csvFile.getChar(&ch) && ch != '\n' && ch != ',')
        {
            if(ch != ' ' && ch != '\t')
            {
                mError = true;
                mErrorString = QObject::tr("В CSV после закрывающей кавычки "
                                           "идет текст");
                return ReadElementStatus::RowContinues;
            }
        }
        if(ch == ',')
            return ReadElementStatus::RowContinues;
        else
            return ReadElementStatus::RowEnded;
    }
}

bool CsvLoader::error() const
{
    return mError;
}

const QString& CsvLoader::errorString() const
{
    return mErrorString;
}
