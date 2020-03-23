﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // отримуємо випадкову кількість стовбців та рядків
    int count = randomBetween(1,12);

    // змінюємо значення компонентів на формі
    ui->lineEdit->setText(getRandom(count));
    ui->lineEdit_2->setText(getRandom(count));
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    buildTable(ui->lineEdit->text(),arg1);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    buildTable(arg1,ui->lineEdit_2->text());
}


// функція для перевірки чи є матриця квадратною
bool MainWindow::isSquare(QStringList input1, QStringList input2)
{
    // якщо в обох масивах однакова кількість елементів
   if (input1.length() == input2.length())
        return true;
    else
        return false;
}


// функція для побудови таблиці
void MainWindow::buildTable(QString input1, QString input2)
{

    returnState();
    // робимо два масиви
    QStringList inArr1 = input1.split(" ");
    QStringList inArr2 = input2.split(" ");

    inArr1.removeAt(inArr1.length() - 1);
    inArr2.removeAt(inArr2.length() - 1);

    // якщо матриця не квадратна
    if (!isSquare(inArr1, inArr2))
    {   // повідомлення про помилку
        ui->label_10->show();
        return;
    }
    ui->label_10->hide();
    // втсановлюємо розміри
    ui->tableWidget->setRowCount(inArr1.length());
    ui->tableWidget->setColumnCount(inArr1.length());
    // встановлюємо заголовки
    ui->tableWidget->setHorizontalHeaderLabels(inArr1);
    ui->tableWidget->setVerticalHeaderLabels(inArr2);
    // усього елементів
    int all = (inArr1.length()) * (inArr1.length());
    // проходимо через кожен елемент
    for (int i = 0; i < all;i++)
    {   // встановлюємо рядок і стовпець
        int row = i / (inArr1.length());
        int column = i % (inArr1.length());
        // встановлюємо значення
        QTableWidgetItem * item = new QTableWidgetItem(QString::number(compare(inArr1[column].toInt(),inArr2[row].toInt())));

        ui->tableWidget->setItem(row, column, item);
    }
    // змінюємо розміри таблиці
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();

    startTestCases();
}


// функція для порівняння
bool MainWindow::compare(int a, int b)
{
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A > B")
        return a > b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A >= B")
        return a >= b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A = B")
        return a == b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD B = 0")
        return  (a % b == 0);
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD 2 = 0 OR B MOD 2 = 0")
        return ((a%2==0) && (b %2 != 0)) || ((b%2==0) && (a%2 != 0));
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD 2 = 0 AND B MOD 2 = 0")
        return ((a%2==0) && (b %2 == 0));
}


// Перевірка властивостей
void MainWindow::startTestCases()
{
    symmetrical();
}

// Повернення у початковий стан
void MainWindow::returnState()
{
    ui->label_3->setText("SYMMETRICAL");
}


// Перевірка на симетричність
void MainWindow::symmetrical(){
    // отримуємо рядки і стовпці
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {   // якщо хоча б один не симетричний
            if (ui->tableWidget->item(i,j) != ui->tableWidget->item(j,i)){
                ui->label_3->setText(ui->label_3->text() + " - ");
                return;
            }
        }

    }
}
