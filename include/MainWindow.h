#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //! Путь к последнему открытому файлу
    QString lastFileOpenPath;

private slots:
    /*!
     * \brief Открывает таблицу SQLite или CSV по нажатии кнопки "Открыть..."
     *        в меню "Файл"
     */
    void fileOpen();

    //! Закрывает приложение при нажатии кнопки "Выход" в меню "Файл"
    void fileQuit();
};

#endif // MAINWINDOW_H
