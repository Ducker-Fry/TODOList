#include "DatabaseManager.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent) {
    // 使用SQLite驱动（移除了所有MySQL相关配置）
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initDatabase(const QString& dbPath) {
    m_db.setDatabaseName(dbPath); // 设置数据库文件名
    
    if (!m_db.open()) {
        qDebug() << "Failed to open SQLite database:" << m_db.lastError().text();
        return false;
    }
    
    return createTables();
}

QSqlDatabase DatabaseManager::database() const
{
    return QSqlDatabase();
}

bool DatabaseManager::createTables() {
    QSqlQuery query(m_db);
    // 修正SQL语法：
    // - AUTOINCREMENT (SQLite的自增关键字)
    // - INTEGER (替代BOOLEAN，SQLite用0/1表示布尔值)
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS tasks ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "title TEXT NOT NULL,"
                               "description TEXT,"
                               "priority INTEGER DEFAULT 1,"
                               "due_date DATE,"
                               "completed INTEGER DEFAULT 0,"  // 使用INTEGER而非BOOLEAN
                               "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                               ")";
    
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool DatabaseManager::backupDatabase(const QString& backupPath) {
    // 实现数据库备份逻辑
    return false;
}


