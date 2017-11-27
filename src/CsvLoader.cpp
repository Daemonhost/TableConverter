#include "CsvLoader.h"

#include <QFile>
#include <QBuffer>
#include <QByteArray>
#include <QMessageBox>
#include <QString>
#include <QVariant>

void CsvLoader::readCsv(QString fileName)
{
    QFile csvFile(fileName);
    csvFile.open(QFile::ReadOnly);
    buffer.open(QBuffer::ReadWrite);
    buffer.write(csvFile.readAll());
    csvRowCount = 0; //Счетчик кол-ва строк
    csvColumnCount = 1; //Счетчик кол-ва столбцов
    buffer.seek(0);
    while(!buffer.atEnd())
    {
        buffer.getChar(&ch);
        if (ch == '\n') csvRowCount++;
    }
    buffer.seek(0);
    do
    {
        buffer.getChar(&ch);
        if (flag)
        {
            if (ch == '"')
            {
                flag = false;
            }
            else
            {
                if (ch == ',') csvColumnCount++;
            }
        }
        else
        {
            if (ch == '"')
            {
                flag = true;
            }
        }
    }
    while  (ch != '\n');
    return;
}

QString CsvLoader::readCsvData()
{
    QString result;
    //Если метод запускается впервые
    if (csvReadDataStart)
    {
        buffer.seek(0); //Каретка на нуль
        csvReadDataStart=false; //Флаг опустить
        pointold = pointnew = 0;
    }
    buffer.getChar(&ch);
    if (ch == '"') flag = false; //Является ли первый элемент кавычками?
    buffer.seek(pointold);
    if (flag) //Нет, кавычек нет
    {
        //Вычисляем размер объекта
        do
        {
            buffer.getChar(&ch);
            pointnew++;
        }
        while ((ch != ('\n')) && (ch != (',')) && (!buffer.atEnd()));
        char word[pointnew-pointold-1]; //Инициализируем соотвествующего размера массив
        buffer.seek(pointold); //Возврат каретки на начало объекта
        counter = 0;
        do
        {
            word[counter]=ch;
            counter++;
            buffer.getChar(&ch);
        }
        while ((ch != ('\n')) && (ch != (',')) && (!buffer.atEnd()));
        if (buffer.atEnd()) //Исправление потери символа на конце файла
        {
            ch = word[0];
            word[0] = word[counter];
            word[counter] = ch;
        }
        pointold=pointnew;
        result = word;
    }
    else //Да, кавычки есть
    {
        buffer.getChar(&ch);
        pointold+=1;
        pointnew+=1; //Перемещаем каретку дальше, долой с кавычек, не забывая учесть их при задании размера массива
        //Вычисляем размер объекта
        do
        {
            pointnew++;
            buffer.getChar(&ch);
        }
        while (ch != '"');
        buffer.seek(pointold); //Возврат каретки на начало объекта
        char word[pointnew-pointold+1]; //Инициализируем соотвествующего размера массив, учитывая кавычки
        counter = 1;
        do
        {
            buffer.getChar(&ch);
            word[counter]=ch;
            counter++;
        }
        while (ch != '"');
        buffer.getChar(&ch);
        word[0]=word[pointnew-pointold]='"'; //Заполняем начало и конец кавычками
        pointnew+=1;
        pointold=pointnew;
        flag = true; //Поднимаем флаг обратно, кавычки пройдены
        result = word;
    }
    return result;
}