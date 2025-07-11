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
    StatisticalChart(QWidget *parent = nullptr);
    ~StatisticalChart();

    void createPriorityDistributionChart();
    void createDailyCompletionChart();
    void setStatisticsManager(StatisticsManager* statisticsManager);
private:
    Ui::StatisticalChartClass ui;
    StatisticsManager* m_statisticsManager;
    PieChartWidget* pieChartWidget = nullptr;
    BarChartWidget* barChartWidget = nullptr;
};

