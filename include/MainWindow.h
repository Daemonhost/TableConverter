#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <TableSelectionDialog.h>

namespace Ui {
class MainWindow;
}

/*!
 * \brief Главное окно.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Создает \p MainWindow с данным родителем
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //! Путь к последнему открытому или сохраненному файлу
    QString lastFilePath;

    //! Расширение последнего открытого файла
    QString lastOpenFileFilter;

    //! Расширение последнего сохрененного файла
    QString lastSavedFileFilter;

    static const QString csvFilter;
    static const QString dbFilter;

    TableSelectionDialog tableSelectionDialog;

private slots:
    /*!
     * \brief Открывает таблицу SQLite или CSV по нажатии кнопки "Открыть..."
     *        в меню "Файл"
     */
    void fileOpen();

    /*!
     * \brief Сохраняет таблицу в SQLite или в CSV по нажатии кнопки
     *        "Сохранить как..." в меню "Файл"
     */
    void fileSaveAs();

    //! Закрывает приложение при нажатии кнопки "Выход" в меню "Файл"
    void fileQuit();
};

#endif // MAINWINDOW_H
