#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <QBuffer>
#include <QString>

class CsvLoader
{
private:
    QBuffer buffer; //Буфер для хранения данных из файла
    char ch; //Переменная для поочередной записи символов
    bool csvReadDataStart = true; //Флаг первичного запуска считывания данных
    bool noQuotes = true; //Флаг, означающий отсутствие кавычек
    ushort counter; // Служебный счетчик
    int pointold; // Служебная переменная для хранения старой позиции каретки при чтении
    int pointnew; // Служебная переменная для хранения новой позиции каретки при чтении
public:
    int csvRowCount; //Счетчик кол-ва строк
    int csvColumnCount; //Счетчик кол-ва столбцов

    //Метод, осуществляющий проверку, является ли csv файл пустым. Если файл пуст, возвращает true
    bool emptyCsvCheck();

    //Метод, открывающий файл csv и заносящий данные в buffer
    void openCsv (QString fileName);

    //Метод, считающий кол-во строк и столбцов csv файла
    void readCsvRowColumn ();

    //Метод, считывающий данные
    QString readCsvData();
};

#endif // CSVLOADER_H
