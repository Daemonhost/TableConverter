#include <QString>
#include <QtTest>
#include <QTemporaryFile>
#include "CsvReader.h"
#include "CsvWriter.h"
#include "SqliteReader.h"
#include "SqliteWriter.h"
#include "TableModel.h"
#include "utility.h"

using namespace std;

class TestSuite : public QObject
{
    Q_OBJECT

private:
    unique_ptr<TableModel> model;

private slots:
    void tableModelTest();
    void csvWriteReadTest();
    void sqliteWriteReadTest();

    void initTestCase();
    void cleanupTestCase();
};

void TestSuite::tableModelTest()
{
    TableModel model;
    model.setColumnCount(2);
    QVERIFY2(model.columnCount() == 2, "setColumnCount");

    model.setRowCount(1);
    QVERIFY2(model.rowCount() == 1, "setRowCount");

    model.resize(3, 2);
    QVERIFY2(model.rowCount() == 3 && model.columnCount() == 2, "resize");

    model.appendRow();
    QVERIFY2(model.rowCount() == 4, "appendRow");

    model.setHeaderData(0, "col1");
    QVERIFY2(model.headerData(0) == "col1", "setHeaderData");

    model.setData(0, 1, "data");
    QVERIFY2(model.data(0, 1) == "data", "setData");
}

void TestSuite::csvWriteReadTest()
{
    // Записываем таблицу в csv, потом ее же считываем и проверяем, что
    // считанная таблица равна исходной
    QTemporaryFile csvFile;
    if(!csvFile.open())
        QFAIL("Не удалось создать временный файл");

    CsvWriter writer;
    writer.write(csvFile.fileName(), model.get());

    CsvReader reader;
    unique_ptr<TableModel> readModel(reader.read(csvFile.fileName()));
    csvFile.close();

    QVERIFY2(tableModelEquals(*model, *readModel), "Таблицы не равны");
}

void TestSuite::sqliteWriteReadTest()
{
    // Записываем таблицу в sqlite, потом ее же считываем и проверяем, что
    // считанная таблица равна исходной
    QTemporaryFile dbFile;
    if(!dbFile.open())
        QFAIL("Не удалось создать временный файл");

    SqliteWriter writer("WriteDbConection");
    writer.open(dbFile.fileName());
    writer.write("table1", model.get());

    SqliteReader reader("ReadDbConection");
    reader.open(dbFile.fileName());
    unique_ptr<TableModel> readModel(reader.read("table1"));
    dbFile.close();

    QVERIFY2(tableModelEquals(*model, *readModel), "Таблицы не равны");
}

void TestSuite::initTestCase()
{
    model = createModelFrom(
                QVector<QVariant> {"col1", "col2", "col3"},
    QVector<QVector<QVariant>> {
        {1, 10.5, "ab\nc"},
        {2, 11.0, "de\"f"}
    });
}

void TestSuite::cleanupTestCase()
{
    model.reset();
}

QTEST_APPLESS_MAIN(TestSuite)

#include "TestSuite.moc"
