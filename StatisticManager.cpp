#include "StatisticManager.h"

StatisticsManager::StatisticsManager(TaskModel* taskModel, QObject* parent)
    : QObject(parent), m_taskModel(taskModel) {}

int StatisticsManager::totalTasks() const {
    return m_taskModel->rowCount();
}

int StatisticsManager::completedTasks() const {
    int count = 0;
    for (int i = 0; i < m_taskModel->rowCount(); ++i) {
        if (m_taskModel->data(m_taskModel->index(i, TaskModel::CompletedColumn)).toBool()) {
            count++;
        }
    }
    return count;
}

int StatisticsManager::pendingTasks() const {
    return totalTasks() - completedTasks();
}

int StatisticsManager::overdueTasks() const {
    int count = 0;
    for (int i = 0; i < m_taskModel->rowCount(); ++i) {
        QDate dueDate = QDate::fromString(
            m_taskModel->data(m_taskModel->index(i, TaskModel::DueDateColumn)).toString(), 
            "yyyy-MM-dd"
        );
        bool completed = m_taskModel->data(m_taskModel->index(i, TaskModel::CompletedColumn)).toBool();
        
        if (!completed && dueDate.isValid() && dueDate < QDate::currentDate()) {
            count++;
        }
    }
    return count;
}

QMap<int, int> StatisticsManager::priorityDistribution() const {
    QMap<int, int> distribution;
    distribution[Task::Low] = 0;
    distribution[Task::Medium] = 0;
    distribution[Task::High] = 0;
    
    for (int i = 0; i < m_taskModel->rowCount(); ++i) {
        int priority = m_taskModel->data(m_taskModel->index(i, TaskModel::PriorityColumn)).toInt();
        distribution[priority]++;
    }
    
    return distribution;
}

QMap<QDate, int> StatisticsManager::dailyTaskCompletion() const {
    QMap<QDate, int> completionMap;
    
    for (int i = 0; i < m_taskModel->rowCount(); ++i) {
        bool completed = m_taskModel->data(m_taskModel->index(i, TaskModel::CompletedColumn)).toBool();
        if (completed) {
            // 实际应用中可能需要记录完成日期，这里简化处理
            QDate dueDate = QDate::fromString(
                m_taskModel->data(m_taskModel->index(i, TaskModel::DueDateColumn)).toString(), 
                "yyyy-MM-dd"
            );
            completionMap[dueDate]++;
        }
    }
    
    return completionMap;
}

QMap<QString, int> StatisticsManager::weeklyTaskCompletion() const {
    // 实现类似 dailyTaskCompletion，按周统计
    return QMap<QString, int>();
}

QMap<QString, int> StatisticsManager::monthlyTaskCompletion() const {
    // 实现类似 dailyTaskCompletion，按月统计
    return QMap<QString, int>();
}

QMap<QDate, int> StatisticsManager::taskCreationTrend(int days) const {
    QMap<QDate, int> trend;
    QDate currentDate = QDate::currentDate();
    
    // 初始化日期范围
    for (int i = days; i >= 0; --i) {
        trend[currentDate.addDays(-i)] = 0;
    }
    
    // 统计每天创建的任务数
    for (int i = 0; i < m_taskModel->rowCount(); ++i) {
        QDate createdAt = QDate::fromString(
            m_taskModel->data(m_taskModel->index(i, TaskModel::CreatedAtColumn)).toString(), 
            "yyyy-MM-dd"
        );
        if (createdAt.isValid() && trend.contains(createdAt)) {
            trend[createdAt]++;
        }
    }
    
    return trend;
}
