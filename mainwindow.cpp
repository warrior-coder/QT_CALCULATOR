#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
    создает фактические экземпляры виджетов
    форма, которую мы создаем в QtDesigner, сохраняется как XML файл
    */
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/new/images/icon.png"));

    /*
    connect() создает заданное соединение из сигнала в объекте отправителя и методе слота в объекте получателя
    */
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

    labelFont = ui->resultLabel->font();
    labelFont.setPixelSize(55);
    ui->resultLabel->setFont(labelFont);
    ui->resultLabel->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// событие нажатия клавиши
void MainWindow::keyPressEvent(QKeyEvent* ke)
{
    switch(ke->key())
    {
        case Qt::Key_0:         ui->pushButton_0->animateClick(); break;
        case Qt::Key_1:         ui->pushButton_1->animateClick(); break;
        case Qt::Key_2:         ui->pushButton_2->animateClick(); break;
        case Qt::Key_3:         ui->pushButton_3->animateClick(); break;
        case Qt::Key_4:         ui->pushButton_4->animateClick(); break;
        case Qt::Key_5:         ui->pushButton_5->animateClick(); break;
        case Qt::Key_6:         ui->pushButton_6->animateClick(); break;
        case Qt::Key_7:         ui->pushButton_7->animateClick(); break;
        case Qt::Key_8:         ui->pushButton_8->animateClick(); break;
        case Qt::Key_9:         ui->pushButton_9->animateClick(); break;

        case Qt::Key_Delete:    ui->pushButton_AC->animateClick(); break;
        case Qt::Key_Backspace: ui->pushButton_C->animateClick(); break;

        case Qt::Key_Period:    ui->pushButton_DOT->animateClick(); break;
        case Qt::Key_Comma:     ui->pushButton_DOT->animateClick(); break;
        case Qt::Key_Shift:     ui->pushButton_REV->animateClick(); break;

        case Qt::Key_Plus:      ui->pushButton_ADD->animateClick(); break;
        case Qt::Key_Minus:     ui->pushButton_SUB->animateClick(); break;
        case Qt::Key_Asterisk:  ui->pushButton_MUL->animateClick(); break;
        case Qt::Key_Slash:     ui->pushButton_DIV->animateClick(); break;

        case Qt::Key_Enter:     ui->pushButton_RES->animateClick(); break;

        case Qt::Key_Escape:    this->close();
    }
}

void MainWindow::on_pushButton_AC_clicked()
{
    has_dot = false;
    clear = false;
    ui->resultLabel->setText("0");
    op = 0;

    labelFont.setPixelSize(55);
    ui->resultLabel->setFont(labelFont);
}

void MainWindow::on_pushButton_C_clicked()
{
    has_dot = false;
    ui->resultLabel->setText("0");

    labelFont.setPixelSize(55);
    ui->resultLabel->setFont(labelFont);
}

void MainWindow::on_pushButton_DOT_clicked()
{
    if (clear)
    {
        ui->resultLabel->setText("0.");
        has_dot = true;
        clear = false;

        labelFont.setPixelSize(55);
        ui->resultLabel->setFont(labelFont);
    }
    else if (!has_dot)
    {
         ui->resultLabel->setText(ui->resultLabel->text() + ".");
         has_dot = true;
    }
}

void MainWindow::on_pushButton_REV_clicked()
{
    QString text = ui->resultLabel->text();
    if (text[0] == '-') text.erase(text.begin(), text.begin() + 1);
    else text.push_front('-');
    ui->resultLabel->setText(text);
}

void MainWindow::on_pushButton_ADD_clicked()
{
    op = '+';
    has_dot = false;
    clear = true;
    value_1 = ui->resultLabel->text().toDouble();
}

void MainWindow::on_pushButton_SUB_clicked()
{
    op = '-';
    has_dot = false;
    clear = true;
    value_1 = ui->resultLabel->text().toDouble();
}

void MainWindow::on_pushButton_MUL_clicked()
{
    op = '*';
    has_dot = false;
    clear = true;
    value_1 = ui->resultLabel->text().toDouble();
}

void MainWindow::on_pushButton_DIV_clicked()
{
    op = '/';
    has_dot = false;
    clear = true;
    value_1 = ui->resultLabel->text().toDouble();
}

void MainWindow::on_pushButton_RES_clicked()
{
    if (op)
    {
        double value_2 = ui->resultLabel->text().toDouble();
        double value_res = value_1;

        switch(op)
        {
        case '+': value_res += value_2; break;
        case '-': value_res -= value_2; break;
        case '*': value_res *= value_2; break;
        case '/': value_res /= value_2; break;
        }

        QString text = QString::number(value_res, 'g', 10);
        ui->resultLabel->setText(text);

        if (text.length() > 10) labelFont.setPixelSize(27);
        else if (text.length() > 5) labelFont.setPixelSize(40);
        else labelFont.setPixelSize(55);
        ui->resultLabel->setFont(labelFont);

        clear = true;
        has_dot = false;
        value_1 = value_res;
        op = 0;
    }
}

void MainWindow::on_pushButton_DIGIT_clicked()
{
    // sender() возвращает указатель на объект, отправивший сигнал
    QPushButton *pb = (QPushButton*)sender();

    int digit = pb->text().toInt();
    QString text = ui->resultLabel->text();

    if (clear)
    {
        text = QString::number(digit);
        clear = false;
    }
    else if (ui->resultLabel->text().size() < 10)
    {
        if (text == "0")
        {
            text = QString::number(digit);
        }
        else
        {
            text = ui->resultLabel->text() + QString::number(digit);
        }

    }
    ui->resultLabel->setText(text);

    labelFont = ui->resultLabel->font();
    if (text.length() > 10) labelFont.setPixelSize(27);
    else if (text.length() > 5) labelFont.setPixelSize(40);
    else labelFont.setPixelSize(55);
    ui->resultLabel->setFont(labelFont);
}
