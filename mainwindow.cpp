#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_countOkButton_clicked()
{
    getSize();
}


void MainWindow::on_Sort_clicked()
{
    bool ok {false};
    ui->arrayView->item(0,0)->text().toInt(&ok);

    if(ok)
        Sort();
    else
        SortDouble();
}


void MainWindow::on_CheckArr_clicked()
{
    bool ok {false};
    ui->arrayView->item(0,0)->text().toInt(&ok);

    if(ok)
        isSorted();
    else
        isSortedDouble();
}


void MainWindow::on_generateButton_clicked()
{
    fillIntArray();
}


void MainWindow::on_generateFloatNumsButton_clicked()
{
    fillDoubleArray();
}


void MainWindow::on_arrayView_itemChanged(QTableWidgetItem *item)
{
    SyncArrays(item);
}


void MainWindow::on_IndividualTask_clicked()
{
    IndTask();
}

