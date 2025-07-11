#include "StatisticalChart.h"
#include <qlayout.h>

StatisticalChart::StatisticalChart(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    pieChartWidget = new PieChartWidget(this);
    barChartWidget = new BarChartWidget(this);
    layout->addWidget(pieChartWidget);
    layout->addWidget(barChartWidget);
    setLayout(layout);
}

StatisticalChart::~StatisticalChart()
{
    delete pieChartWidget;
    delete barChartWidget;
}

void StatisticalChart::createPriorityDistributionChart()
{
    if (m_statisticsManager)
    {
        QMap<QString, int> data;
        data["Low Priority"] = m_statisticsManager->priorityDistribution()[Task::Low];
        data["Medium Priority"] = m_statisticsManager->priorityDistribution()[Task::Medium];
        data["High Priority"] = m_statisticsManager->priorityDistribution()[Task::High];

        pieChartWidget->setTitle("Task Priority Distribution");
        pieChartWidget->setData(data);
    }
}

void StatisticalChart::createDailyCompletionChart()
{
    if (m_statisticsManager)
    {
        QMap<QString, int> data;
        data["Completed"] = m_statisticsManager->completedTasks();
        data["Pending"] = m_statisticsManager->pendingTasks();
        data["Overdue"] = m_statisticsManager->overdueTasks();

        barChartWidget->setTitle("Task Completion Status");
        barChartWidget->setData(data);
    }
}

void StatisticalChart::setStatisticsManager(StatisticsManager* statisticsManager)
{
    m_statisticsManager = statisticsManager;
}
