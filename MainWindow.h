#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include"Task.h"
#include<qtableview.h>
#include"StatisticalChart.h"


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
    void on_filterButton_clicked();
    void on_priorityComboBox_currentIndexChanged(int index);
    void on_showCompletedCheckBox_stateChanged(int state);
    void on_showOverdueCheckBox_stateChanged(int state);
    void on_startDateEdit_dateChanged(const QDate& date);
    void on_endDateEdit_dateChanged(const QDate& date);

private:
    Ui::MainWindowClass ui;
    QTableView* taskTableView; 
    TaskModel* taskModel;
    StatisticsManager* statisticsManager;
    StatisticalChart* statisticalChart;

    void initFilters();
    void connect_signal_slot();
};

