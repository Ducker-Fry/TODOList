#include "DatabaseManager.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent) {
    // ʹ��SQLite�������Ƴ�������MySQL������ã�
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initDatabase(const QString& dbPath) {
    m_db.setDatabaseName(dbPath); // �������ݿ��ļ���
    
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
    // ����SQL�﷨��
    // - AUTOINCREMENT (SQLite�������ؼ���)
    // - INTEGER (���BOOLEAN��SQLite��0/1��ʾ����ֵ)
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS tasks ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "title TEXT NOT NULL,"
                               "description TEXT,"
                               "priority INTEGER DEFAULT 1,"
                               "due_date DATE,"
                               "completed INTEGER DEFAULT 0,"  // ʹ��INTEGER����BOOLEAN
                               "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                               ")";
    
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool DatabaseManager::backupDatabase(const QString& backupPath) {
    // ʵ�����ݿⱸ���߼�
    return false;
}


