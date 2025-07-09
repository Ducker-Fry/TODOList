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

    void setStatisticsManager(StatisticsManager* statisticsManager);
    void createPriorityDistributionChart();
    void createDailyCompletionChart();
private:
    Ui::StatisticalChartClass ui;
    StatisticsManager* m_statisticsManager;
};

