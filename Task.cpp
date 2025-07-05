#include "Task.h"

Task::Task(int id, const QString& title, const QString& description, Priority priority, const QDate& dueDate, bool completed)
    : m_id(id), m_title(title), m_description(description), 
      m_priority(priority), m_dueDate(dueDate), m_completed(completed) {}

int Task::id() const {
    return m_id;
}

QString Task::title() const {
    return m_title;
}

QString Task::description() const {
    return m_description;
}

Task::Priority Task::priority() const {
    return m_priority;
}

QDate Task::dueDate() const {
    return m_dueDate;
}

bool Task::completed() const {
    return m_completed;
}

void Task::setId(int id) {
    m_id = id;
}

void Task::setTitle(const QString& title) {
    m_title = title;
}

void Task::setDescription(const QString& description) {
    m_description = description;
}

void Task::setPriority(Priority priority) {
    m_priority = priority;
}

void Task::setDueDate(const QDate& dueDate) {
    m_dueDate = dueDate;
}

void Task::setCompleted(bool completed) {
    m_completed = completed;
}

bool Task::isOverdue() const {
    return !m_completed && m_dueDate.isValid() && m_dueDate < QDate::currentDate();
}

QString Task::priorityString() const {
    switch (m_priority) {
        case Low: return "Low";
        case Medium: return "Medium";
        case High: return "High";
        default: return "";
    }
}
