#pragma once

#include <QObject>
#include <QDate>
#include"Task.h"
#include <QMap>

class StatisticsManager : public QObject {
    Q_OBJECT
public:
    explicit StatisticsManager(TaskModel* taskModel, QObject* parent = nullptr);
    
    // ����ͳ��
    int totalTasks() const;
    int completedTasks() const;
    int pendingTasks() const;
    int overdueTasks() const;
    
    // ���ȼ��ֲ�
    QMap<int, int> priorityDistribution() const;
    
    // ������ͳ��
    QMap<QDate, int> dailyTaskCompletion() const;
    QMap<QString, int> weeklyTaskCompletion() const;
    QMap<QString, int> monthlyTaskCompletion() const;
    
    // ��������
    QMap<QDate, int> taskCreationTrend(int days = 30) const;
    
private:
    TaskModel* m_taskModel;
};
