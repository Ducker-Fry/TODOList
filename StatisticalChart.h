#pragma once

#include <QWidget>
#include "ui_StatisticalChart.h"
#include"StatisticManager.h"
#include"PieChart.h"
#include"BarChart.h"

class StatisticalChart : public QWidget
{
    Q_OBJECT

public:
    StatisticalChart(QWidget *parent = nullptr,StatisticsManager* statisticManager = nullptr);
    ~StatisticalChart();

    void createPriorityDistributionChart();
    void createDailyCompletionChart();
private:
    Ui::StatisticalChartClass ui;
    StatisticsManager* m_statisticsManager;
    PieChartWidget* pieChartWidget = nullptr;
    BarChartWidget* barChartWidget = nullptr;
};

