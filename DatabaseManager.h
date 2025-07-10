#pragma once  
#include <QtCore/QObject>  
#include <QtSql/QSqlDatabase> 
#include <QtCore/QString>  
#include<qsqlerror.h>

class DatabaseManager : public QObject {  
  Q_OBJECT  
public:  
  static DatabaseManager& instance();  
  bool initDatabase(const QString& dbPath = "todo.db");  
  QSqlDatabase database() const;  

  // ���ݿ��������  
  bool createTables();  
  bool backupDatabase(const QString& backupPath);  

private:  
  explicit DatabaseManager(QObject* parent = nullptr);  
  ~DatabaseManager();  
  Q_DISABLE_COPY(DatabaseManager)  

  QSqlDatabase m_db;  
};