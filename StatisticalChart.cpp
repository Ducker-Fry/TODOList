#include "StatisticalChart.h"

StatisticalChart::StatisticalChart(QWidget *parent,StatisticsManager* statisticManager)
    : QWidget(parent), m_statisticsManager(statisticManager)
{
    ui.setupUi(this);
}

StatisticalChart::~StatisticalChart()
{}

void StatisticalChart::createPriorityDistributionChart()
{
    pieChartWidget = new PieChartWidget(this);

    QMap<QString, int> data;
    data["Low Priority"] = m_statisticsManager->priorityDistribution()[Task::Low];
    data["Medium Priority"] = m_statisticsManager->priorityDistribution()[Task::Medium];
    data["High Priority"] = m_statisticsManager->priorityDistribution()[Task::High];

    pieChartWidget->setTitle("Task Priority Distribution");
    pieChartWidget->setData(data);
}

void StatisticalChart::createDailyCompletionChart()
{
    barChartWidget = new BarChartWidget(this);

    QMap<QString, int> data;
    data["Completed"] = m_statisticsManager->completedTasks();
    data["Pending"] = m_statisticsManager->pendingTasks();
    data["Overdue"] = m_statisticsManager->overdueTasks();

    barChartWidget->setTitle("Task Completion Status");
    barChartWidget->setData(data);
}
