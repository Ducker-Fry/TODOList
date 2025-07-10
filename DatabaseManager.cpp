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

bool DatabaseManager::initDatabase()
{
    // 尝试直接连接 todo_db 数据库
    if (m_db.open())
    {
        return createTables();
    }

    // 检查错误是否为 "database doesn't exist"
    QString errorText = m_db.lastError().text();
    qDebug() << "Failed to open database:" << errorText;

    // 如果是因为数据库不存在导致的失败，尝试创建数据库
    if (errorText.contains("1049") || errorText.contains("database doesn't exist"))
    {
        // 关闭当前连接
        m_db.close();

        // 创建一个临时连接，连接到 MySQL 系统数据库
        QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL", "tempConnection");
        tempDb.setHostName(m_db.hostName());
        tempDb.setUserName(m_db.userName());
        tempDb.setPassword(m_db.password());
        tempDb.setDatabaseName("mysql"); // 连接到系统数据库

        if (!tempDb.open())
        {
            qDebug() << "Failed to connect to MySQL system database:" << tempDb.lastError().text();
            return false;
        }

        // 创建新数据库
        QSqlQuery query(tempDb);
        if (!query.exec("CREATE DATABASE IF NOT EXISTS todo_db"))
        {
            qDebug() << "Failed to create database:" << query.lastError().text();
            tempDb.close();
            return false;
        }
        tempDb.close();

        // 移除临时连接
        QSqlDatabase::removeDatabase("tempConnection");

        // 重新尝试连接新创建的数据库
        m_db.setDatabaseName("todo_db");
        if (!m_db.open())
        {
            qDebug() << "Failed to open newly created database:" << m_db.lastError().text();
            return false;
        }

        return createTables();
    }

    // 其他错误，返回失败
    return false;
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


