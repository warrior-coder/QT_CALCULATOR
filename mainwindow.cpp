#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // creates a connection of the given type from the signal in the sender object to the method in the receiver object
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(on_pushButton_DIGIT_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* key Press Event */
void MainWindow::keyPressEvent(QKeyEvent* ke)
{
    switch(ke->key())
    {
        case Qt::Key_0:         click_DIGIT(0); break;
        case Qt::Key_1:         click_DIGIT(1); break;
        case Qt::Key_2:         click_DIGIT(2); break;
        case Qt::Key_3:         click_DIGIT(3); break;
        case Qt::Key_4:         click_DIGIT(4); break;
        case Qt::Key_5:         click_DIGIT(5); break;
        case Qt::Key_6:         click_DIGIT(6); break;
        case Qt::Key_7:         click_DIGIT(7); break;
        case Qt::Key_8:         click_DIGIT(8); break;
        case Qt::Key_9:         click_DIGIT(9); break;

        case Qt::Key_Delete:    click_AC(); break;
        case Qt::Key_Backspace: click_C(); break;

        case Qt::Key_Period:    click_DOT(); break;
        case Qt::Key_Shift:     click_REV(); break;

        case Qt::Key_Plus:      click_OPERATION('+'); break;
        case Qt::Key_Minus:     click_OPERATION('-'); break;
        case Qt::Key_Asterisk:  click_OPERATION('*'); break;
        case Qt::Key_Slash:     click_OPERATION('/'); break;

        case Qt::Key_Enter:     click_RES(); break;

        case Qt::Key_Escape:    this->close();
    }
}

/* calculator functions */
void MainWindow::click_DIGIT(int digit)
{
    if (clear)
    {
        ui->resultLabel->setText(QString::number(digit));
        clear = false;
    }
    else if (ui->resultLabel->text().size() < 10)
    {
        QString text = ui->resultLabel->text();
        if (text == "0")
        {
            text = QString::number(digit);
        }
        else
        {
            text += QString::number(digit);
        }
        ui->resultLabel->setText(text);

    }
}
void MainWindow::click_AC()
{
    has_dot = 0;
    ui->resultLabel->setText("0");
    op = false;
}
void MainWindow::click_C()
{
    has_dot = 0;
    ui->resultLabel->setText("0");
}
void MainWindow::click_DOT()
{
    if (clear)
    {
        ui->resultLabel->setText("0.");
        has_dot = 1;
        clear = false;
    }
    else if (has_dot == 0)
    {
         ui->resultLabel->setText(ui->resultLabel->text() + ".");
         has_dot = 1;
    }
}
void MainWindow::click_REV()
{
    double number = ui->resultLabel->text().toDouble();
    number *= -1;
    ui->resultLabel->setText(QString::number(number));
}
void MainWindow::click_OPERATION(char operation)
{
    op = operation;
    has_dot = false;
    clear = true;
    value_1 = ui->resultLabel->text().toDouble();
}
void MainWindow::click_RES()
{
    if (op)
    {
        double value_2 = ui->resultLabel->text().toDouble();
        double value_res = 0;

        switch(op)
        {
        case '+':
            value_res = value_1 + value_2;
        break;

        case '-':
            value_res = value_1 - value_2;
        break;

        case '*':
            value_res = value_1 * value_2;
        break;

        case '/':
            value_res = value_1 / value_2;
        break;
        }

        ui->resultLabel->setText(QString::number(value_res, 'g', 10));
        clear = true;
        has_dot = 0;
        value_1 = value_res;

        op = 0;
    }
}


/* push Button events */
void MainWindow::on_pushButton_DIGIT_clicked()
{
    // returns a pointer to the object that sent the signal
    QPushButton *pb = (QPushButton*)sender();
    click_DIGIT(pb->text().toInt());
}
void MainWindow::on_pushButton_AC_clicked() { click_AC(); }
void MainWindow::on_pushButton_C_clicked() { click_C(); }
void MainWindow::on_pushButton_DOT_clicked() { click_DOT(); }
void MainWindow::on_pushButton_REV_clicked() { click_REV(); }
void MainWindow::on_pushButton_ADD_clicked() { click_OPERATION('+'); }
void MainWindow::on_pushButton_SUB_clicked() { click_OPERATION('-'); }
void MainWindow::on_pushButton_MUL_clicked() { click_OPERATION('*'); }
void MainWindow::on_pushButton_DIV_clicked() { click_OPERATION('/'); }
void MainWindow::on_pushButton_RES_clicked() { click_RES(); }

