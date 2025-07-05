#pragma once  
#include <QtSql/QSqlTableModel>  
#include <QString>  
#include <QDate>  

class Task {  
public:  
    // �������ȼ�ö������
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

   // ��������  
   bool isOverdue() const;  
   QString priorityString() const;  

private:  
    int m_id = -1;  // ����ID, -1��ʾδ����
    QString m_title;  // �������
    QString m_description;  // ��������
    Priority m_priority = Medium;  // �������ȼ�, Ĭ���е�
    QDate m_dueDate;  // �����ֹ����, Ĭ����Ч����
    bool m_completed = false;  // �����Ƿ����, Ĭ��δ���
};  

class TaskModel : public QSqlTableModel 
{  
    Q_OBJECT
public:  
    // ������ö������,��ģ���б������
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

   // �Զ���������ʾ  
   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;  
   bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;  

   // �������  
   bool addTask(const Task& task);  
   bool updateTask(const Task& task);  
   bool deleteTask(int taskId);  
   QList<Task> getAllTasks() const;  

   // ���˷���  
   void setFilterByStatus(bool showCompleted, bool showOverdue);  
   void setSearchText(const QString& text);  
};
