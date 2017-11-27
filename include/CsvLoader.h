#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <QBuffer>
#include <QFile>
#include <QString>

class CsvLoader
{
private:
    QFile csvFile;
    QBuffer buffer;
    char ch;
    int pointold;
    int pointnew;
    ushort counter;
public:
    bool csvReadDataStart = true; //Флаг первичного запуска считывания данных
    bool flag = true; //Флаг, означающие отсутствие кавычек
    int csvRowCount; //Счетчик кол-ва строк
    int csvColumnCount; //Счетчик кол-ва столбцов

    //Метод, считающий кол-во строк и столбцов csv файла
    void readCsv (QString fileName);

    //Метод, считывающий данные
    QString readCsvData();
};

#endif // CSVLOADER_H
