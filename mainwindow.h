#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    // Q_OBJECT macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt meta-object system
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent*) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void click_DIGIT(int);

    void click_AC();
    void click_C();

    void click_DOT();
    void click_REV();

    void click_OPERATION(char);

    void click_RES();


    double value_1;
    int has_dot = false;
    char op = 0;
    bool clear = true;

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
