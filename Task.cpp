#include "Task.h"
#include <QtSql/QSqlQuery> // Ensure QSqlQuery is fully included
#include <QtSql/QSqlError> // For error handling
#include <QDebug>    // For debugging output

Task::Task(int id, const QString& title, const QString& description, Priority priority, const QDate& dueDate, bool completed)
    : m_id(id), m_title(title), m_description(description),
    m_priority(priority), m_dueDate(dueDate), m_completed(completed)
{
}

int Task::id() const
{
    return m_id;
}

QString Task::title() const
{
    return m_title;
}

QString Task::description() const
{
    return m_description;
}

Task::Priority Task::priority() const
{
    return m_priority;
}

QDate Task::dueDate() const
{
    return m_dueDate;
}

bool Task::completed() const
{
    return m_completed;
}

void Task::setId(int id)
{
    m_id = id;
}

void Task::setTitle(const QString& title)
{
    m_title = title;
}

void Task::setDescription(const QString& description)
{
    m_description = description;
}

void Task::setPriority(Priority priority)
{
    m_priority = priority;
}

void Task::setDueDate(const QDate& dueDate)
{
    m_dueDate = dueDate;
}

void Task::setCompleted(bool completed)
{
    m_completed = completed;
}

bool Task::isOverdue() const
{
    return !m_completed && m_dueDate.isValid() && m_dueDate < QDate::currentDate();
}

QString Task::priorityString() const
{
    switch (m_priority)
    {
    case Low: return "Low";
    case Medium: return "Medium";
    case High: return "High";
    default: return "";
    }
}

TaskModel::TaskModel(QObject* parent) : QSqlTableModel(parent)
{
    setTable("tasks");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select(); //更新模型里的数据
}

QVariant TaskModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == PriorityColumn)
        {
            int priority = QSqlTableModel::data(index, role).toInt();
            switch (priority)
            {
            case Task::Low: return "Low";
            case Task::Medium: return "Medium";
            case Task::High: return "High";
            default: return "";
            }
        }
    }
    return QSqlTableModel::data(index, role);
}

bool TaskModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlTableModel::setData(index, value, role);
}

bool TaskModel::addTask(const Task& task)
{
    QSqlQuery query; // Ensure QSqlQuery is fully included and initialized
    // Prepare the SQL query to insert a new task
    query.prepare("INSERT INTO tasks (title, description, priority, due_date, completed) "
        "VALUES (:title, :description, :priority, :due_date, :completed)");
    // Bind the values to the query parameters
    query.bindValue(":title", task.title());
    query.bindValue(":description", task.description());
    query.bindValue(":priority", task.priority());
    query.bindValue(":due_date", task.dueDate().toString("yyyy-MM-dd"));
    query.bindValue(":completed", task.completed());

    if (query.exec())
    {
        select();
        return true;
    }
    else
    {
        qDebug() << "Failed to add task:" << query.lastError().text();
        return false;
    }
}

bool TaskModel::updateTask(const Task& task)
{
    QSqlQuery query; // Ensure QSqlQuery is fully included and initialized
    query.prepare("UPDATE tasks SET title = :title, description = :description, "
        "priority = :priority, due_date = :due_date, completed = :completed "
        "WHERE id = :id");
    query.bindValue(":id", task.id());
    query.bindValue(":title", task.title());
    query.bindValue(":description", task.description());
    query.bindValue(":priority", task.priority());
    query.bindValue(":due_date", task.dueDate().toString("yyyy-MM-dd"));
    query.bindValue(":completed", task.completed());

    if (query.exec())
    {
        select();
        return true;
    }
    else
    {
        qDebug() << "Failed to update task:" << query.lastError().text();
        return false;
    }
}

bool TaskModel::deleteTask(int taskId)
{
    QSqlQuery query; // Ensure QSqlQuery is fully included and initialized
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (query.exec())
    {
        select();
        return true;
    }
    else
    {
        qDebug() << "Failed to delete task:" << query.lastError().text();
        return false;
    }
}

QList<Task> TaskModel::getAllTasks() const
{
    QList<Task> tasks;
    for (int i = 0; i < rowCount(); ++i)
    {
        int id = data(index(i, IdColumn)).toInt();
        QString title = data(index(i, TitleColumn)).toString();
        QString description = data(index(i, DescriptionColumn)).toString();
        int priority = data(index(i, PriorityColumn)).toInt();
        QDate dueDate = QDate::fromString(data(index(i, DueDateColumn)).toString(), "yyyy-MM-dd");
        bool completed = data(index(i, CompletedColumn)).toBool();

        tasks.append(Task(id, title, description, static_cast<Task::Priority>(priority), dueDate, completed));
    }
    return tasks;
}

void TaskModel::setFilterByStatus(bool showCompleted, bool showOverdue)
{
    QString filter;
    if (!showCompleted)
    {
        filter += "completed = 0";
    }
    if (showOverdue)
    {
        if (!filter.isEmpty())
        {
            filter += " AND ";
        }
        filter += "due_date < CURDATE() AND completed = 0";
    }
    setFilter(filter);
    select();
}

void TaskModel::setSearchText(const QString& text)
{
    QString filter = QString("title LIKE '%%1%' OR description LIKE '%%1%'").arg(text);
    setFilter(filter);
    select();
}

