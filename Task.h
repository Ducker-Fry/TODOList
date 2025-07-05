#pragma once
#include <QString>
#include <QDate>

class Task {
public:
    enum Priority { Low = 1, Medium = 2, High = 3 };
    
    Task() = default;
    Task(int id, const QString& title, const QString& description, 
         Priority priority, const QDate& dueDate, bool completed);
    
    // Getters and setters
    int id() const;
    QString title() const;
    QString description() const;
    Priority priority() const;
    QDate dueDate() const;
    bool completed() const;
    
    void setId(int id);
    void setTitle(const QString& title);
    void setDescription(const QString& description);
    void setPriority(Priority priority);
    void setDueDate(const QDate& dueDate);
    void setCompleted(bool completed);
    
    // ¸¨Öú·½·¨
    bool isOverdue() const;
    QString priorityString() const;

private:
    int m_id = -1;
    QString m_title;
    QString m_description;
    Priority m_priority = Medium;
    QDate m_dueDate;
    bool m_completed = false;
};

