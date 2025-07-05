#pragma once  
#include <QtSql/QSqlTableModel>  
#include <QString>  
#include <QDate>  

class Task {  
public:  
    // 任务优先级枚举类型
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

   // 辅助方法  
   bool isOverdue() const;  
   QString priorityString() const;  

private:  
    int m_id = -1;  // 任务ID, -1表示未设置
    QString m_title;  // 任务标题
    QString m_description;  // 任务描述
    Priority m_priority = Medium;  // 任务优先级, 默认中等
    QDate m_dueDate;  // 任务截止日期, 默认无效日期
    bool m_completed = false;  // 任务是否完成, 默认未完成
};  

class TaskModel : public QSqlTableModel 
{  
    Q_OBJECT
public:  
    // 列索引枚举类型,是模型中表的列名
    enum Columns
    {
       IdColumn = 0,  
       TitleColumn,  
       DescriptionColumn,  
       PriorityColumn,  
       DueDateColumn,  
       CompletedColumn,  
       CreatedAtColumn  
   };  

   explicit TaskModel(QObject* parent = nullptr);  

   // 自定义数据显示  
   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;  
   bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;  

   // 任务操作  
   bool addTask(const Task& task);  
   bool updateTask(const Task& task);  
   bool deleteTask(int taskId);  
   QList<Task> getAllTasks() const;  

   // 过滤方法  
   void setFilterByStatus(bool showCompleted, bool showOverdue);  
   void setSearchText(const QString& text);  
};
