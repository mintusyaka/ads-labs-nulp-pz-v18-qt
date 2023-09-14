#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <vector>
#include <ctime>
#include <QMainWindow>
#include <QLineEdit>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_countOkButton_clicked();

    void on_Sort_clicked();

    void on_CheckArr_clicked();

    void on_generateButton_clicked();

    void on_generateFloatNumsButton_clicked();

    void on_arrayView_itemChanged(QTableWidgetItem *item);

    void on_IndividualTask_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<int> intArray;
    std::vector<double> doubleArray;

    int curSize {0};

    void ShowSize() {
        ui->howManyNum->setText(QString::number(curSize));
    }

    void AddRow() {
        ui->arrayView->setRowCount(1);
    }

    void AddElementToArr(int value) {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(value));

        int _size { ui->arrayView->columnCount() };
        ui->arrayView->setColumnCount(_size + 1);
        ui->arrayView->setItem(0, _size, x);
    }

    void AddElementToArr(double value) {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(value, 'f', 3));

        int _size { ui->arrayView->columnCount() };
        ui->arrayView->setColumnCount(_size + 1);
        ui->arrayView->setItem(0, _size, x);
    }

    void DeleteElements() {
        ui->arrayView->removeRow(0);
        ui->arrayView->setColumnCount(0);
    }

    void getSize() {
        QString input_text {ui->countLine->text()};
        bool bValid {0};
        curSize = input_text.toInt(&bValid);

        if(!bValid)
            ui->statusbar->showMessage("Ви маєте ввести цілочисельне значення від 0 до 2147483647!");

        else
            ui->statusbar->showMessage("Успішно задано розмір масиву!");


        DeleteElements();
        intArray.clear();
        doubleArray.clear();

        ShowSize();
    }

    void fillIntArray() {
        DeleteElements();
        intArray.clear();

        if(curSize > 0) {
            AddRow();
            for(int i = 0; i < curSize; ++i) {
                intArray.push_back(rand() % 100);
                AddElementToArr(intArray[i]);
            }
        }
    }

    void fillDoubleArray() {
        DeleteElements();
        doubleArray.clear();

        if(curSize > 0) {
            AddRow();
            for(int i = 0; i < curSize; ++i) {
                doubleArray.push_back((rand() % 1000));
                doubleArray[i] /=  100;
                AddElementToArr(doubleArray[i]);
            }
        }
    }

    void isSorted() {
        bool sortStatus {true};
        for(int i = 1; i < curSize; ++i) {
            if(intArray[i] < intArray[i - 1]) {
                sortStatus = false;
                break;
            }
        }

        if(sortStatus)
            ui->statusbar->showMessage("Масив відсортований!");
        else
            ui->statusbar->showMessage("Масив не відсортований!");
    }

    void isSortedDouble() {
        bool sortStatus {true};
        for(int i = 1; i < curSize; ++i) {
            if(doubleArray[i] < doubleArray[i - 1]) {
                sortStatus = false;
                break;
            }
        }

        if(sortStatus)
            ui->statusbar->showMessage("Масив відсортований!");
        else
            ui->statusbar->showMessage("Масив не відсортований!");
    }

    void Sort() {
        auto begin_time = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < curSize; ++i) {
            std::vector<int>::iterator min {intArray.begin() + i};
            for(int j = i; j < curSize; ++j) {
                if(*min > intArray[j]) {
                    min = intArray.begin() + j;
                }
            }
            int temp = intArray[i];
            intArray[i] = *min;
            *min = temp;

            ui->arrayView->item(0, i)->setText(QString::number(intArray[i]));
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);

        ui->timeNum->setText(QString::number(duration.count()));

        isSorted();

    }

    void SortDouble() {
        auto begin_time = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < curSize; ++i) {
            std::vector<double>::iterator min {doubleArray.begin() + i};
            for(int j = i; j < curSize; ++j) {
                if(*min > doubleArray[j]) {
                    min = doubleArray.begin() + j;
                }
            }
            double temp = doubleArray[i];
            doubleArray[i] = *min;
            *min = temp;

            ui->arrayView->item(0, i)->setText(QString::number(doubleArray[i], 'f', 3));
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);

        ui->timeNum->setText(QString::number(duration.count()));

        isSortedDouble();

    }

    void SyncArrays(QTableWidgetItem *item) {
        bool ok {false};
        ui->arrayView->item(0, 0)->text().toInt(&ok);

        int j {item->column()};
        if(ok) {
            intArray[j] = item->text().toInt();
        }
        else {
            doubleArray[j] = item->text().toDouble();
        }
    }

    void IndTask() {
        auto begin_time = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < curSize; ++i) {
            std::vector<double>::iterator max {doubleArray.begin() + i};
            for(int j = i; j < curSize; ++j) {
                if(*max < doubleArray[j]) {
                    max = doubleArray.begin() + j;
                }
            }
            double temp = doubleArray[i];
            doubleArray[i] = *max;
            *max = temp;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);

        ui->timeNum->setText(QString::number(duration.count()));

        doubleArray.erase(doubleArray.begin());
        --curSize;
        doubleArray.erase(doubleArray.begin() + curSize - 1);
        --curSize;

        DeleteElements();
        AddRow();

        ShowSize();

        for(int i = 0; i < curSize; ++i) {
            AddElementToArr(doubleArray[i]);
        }


    }
};
#endif // MAINWINDOW_H
