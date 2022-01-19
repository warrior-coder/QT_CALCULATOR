#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
MainWindow обеспечивает основу для создания пользовательского интерфейса приложения (user interface)
Qt имеет QMainWindow и связанные с ним классы для управления главным окном
QMainWindow имеет собственный макет
*/
class MainWindow : public QMainWindow
{
    /*
    все классы, унаследованные от QObject, могут содержать сигналы и слоты
    макрос Q_OBJECT должен отображаться в private секции класса, который объявляет свои собственные сигналы и слоты или другие сервисы, предоставляемые системой метаобъектов Qt (Qt meta-object system)
    */
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent*) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    double value_1 = 0;
    int has_dot = false;
    char op = 0;
    bool clear = true;
    QFont labelFont;

/*
механизм сигналов и слотов является центральной особенностью Qt, они используются для связи между объектами
сигнал испускается, когда происходит определенное событие
слот – это функция, которая вызывается в ответ на определенный сигнал
*/
private slots:
    void on_pushButton_DIGIT_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_C_clicked();
    void on_pushButton_DOT_clicked();
    void on_pushButton_REV_clicked();
    void on_pushButton_ADD_clicked();
    void on_pushButton_SUB_clicked();
    void on_pushButton_MUL_clicked();
    void on_pushButton_DIV_clicked();
    void on_pushButton_RES_clicked();
};
#endif // MAINWINDOW_H
