#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include"Task.h"
#include<qtableview.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_updateButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::MainWindowClass ui;
    QTableView* taskTableView; 
    TaskModel* taskModel;
};

