#pragma once

#include <QWidget>
#include "ui_StatisticalChart.h"

class StatisticalChart : public QWidget
{
    Q_OBJECT

public:
    StatisticalChart(QWidget *parent = nullptr);
    ~StatisticalChart();

private:
    Ui::StatisticalChartClass ui;
};

