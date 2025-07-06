#pragma once

#include <QObject>
#include <QDate>
#include"Task.h"
#include <QMap>

class StatisticsManager : public QObject {
    Q_OBJECT
public:
    explicit StatisticsManager(TaskModel* taskModel, QObject* parent = nullptr);
    
    // 基本统计
    int totalTasks() const;
    int completedTasks() const;
    int pendingTasks() const;
    int overdueTasks() const;
    
    // 优先级分布
    QMap<int, int> priorityDistribution() const;
    
    // 按日期统计
    QMap<QDate, int> dailyTaskCompletion() const;
    QMap<QString, int> weeklyTaskCompletion() const;
    QMap<QString, int> monthlyTaskCompletion() const;
    
    // 任务趋势
    QMap<QDate, int> taskCreationTrend(int days = 30) const;
    
private:
    TaskModel* m_taskModel;
};
