#include "DatabaseManager.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent) {
    // 初始化数据库驱动
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("todo_db");
    m_db.setUserName("root");
    m_db.setPassword("112106120Sql@");
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initDatabase(const QString& dbPath) {
    if (!m_db.open()) {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }
    return createTables();
}

QSqlDatabase DatabaseManager::database() const {
    return m_db;
}

bool DatabaseManager::createTables() {
    QSqlQuery query(m_db);
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS tasks ("
                               "id INTEGER PRIMARY KEY AUTO_INCREMENT,"
                               "title TEXT NOT NULL,"
                               "description TEXT,"
                               "priority INTEGER DEFAULT 1,"
                               "due_date DATE,"
                               "completed BOOLEAN DEFAULT 0,"
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


