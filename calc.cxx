#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect all the digit buttons to a single slot
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    // ... repeat for all digits 2-9
    
    // Connect operator buttons
    connect(ui->pushButton_plus, &QPushButton::clicked, this, &MainWindow::on_operator_pressed);
    connect(ui->pushButton_minus, &QPushButton::clicked, this, &MainWindow::on_operator_pressed);
    // ... repeat for multiplication and division

    // Connect the equals and clear buttons
    connect(ui->pushButton_equals, &QPushButton::clicked, this, &MainWindow::on_equals_pressed);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::on_clear_pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot to handle all digit presses
void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText + button->text());
}

// Slot to handle operator presses
void MainWindow::on_operator_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    // Store the first number and the operator
    first_number = ui->lineEdit->text().toDouble();
    operator_symbol = button->text();
    ui->lineEdit->clear();
}

// Slot to calculate the result
void MainWindow::on_equals_pressed()
{
    double second_number = ui->lineEdit->text().toDouble();
    double result = 0.0;

    if (operator_symbol == "+") {
        result = first_number + second_number;
    } else if (operator_symbol == "-") {
        result = first_number - second_number;
    } else if (operator_symbol == "x") {
        result = first_number * second_number;
    } else if (operator_symbol == "/") {
        if (second_number != 0) {
            result = first_number / second_number;
        } else {
            // Handle division by zero error
            ui->lineEdit->setText("Error");
            return;
        }
    }
    ui->lineEdit->setText(QString::number(result));
}

// Slot to clear the display
void MainWindow::on_clear_pressed()
{
    ui->lineEdit->clear();
}


