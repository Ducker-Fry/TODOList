#include "StatisticalChart.h"

StatisticalChart::StatisticalChart(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

StatisticalChart::~StatisticalChart()
{}

void StatisticalChart::setStatisticsManager(StatisticsManager * statisticsManager)
{
    m_statisticsManager = statisticsManager;
}

void StatisticalChart::createPriorityDistributionChart()
{
    PieChartWidget* chartWidget = new PieChartWidget(this);

    QMap<QString, int> data;
    data["Low Priority"] = m_statisticsManager->priorityDistribution()[Task::Low];
    data["Medium Priority"] = m_statisticsManager->priorityDistribution()[Task::Medium];
    data["High Priority"] = m_statisticsManager->priorityDistribution()[Task::High];

    chartWidget->setTitle("Task Priority Distribution");
    chartWidget->setData(data);
}

void StatisticalChart::createDailyCompletionChart()
{
    BarChartWidget* chartWidget = new BarChartWidget(this);

    QMap<QString, int> data;
    data["Completed"] = m_statisticsManager->completedTasks();
    data["Pending"] = m_statisticsManager->pendingTasks();
    data["Overdue"] = m_statisticsManager->overdueTasks();

    chartWidget->setTitle("Task Completion Status");
    chartWidget->setData(data);
}
