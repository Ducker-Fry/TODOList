#include "DatabaseManager.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent) {
    // ��ʼ�����ݿ�����
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
    // ����ֱ������ todo_db ���ݿ�
    if (m_db.open())
    {
        return createTables();
    }

    // �������Ƿ�Ϊ "database doesn't exist"
    QString errorText = m_db.lastError().text();
    qDebug() << "Failed to open database:" << errorText;

    // �������Ϊ���ݿⲻ���ڵ��µ�ʧ�ܣ����Դ������ݿ�
    if (errorText.contains("1049") || errorText.contains("database doesn't exist"))
    {
        // �رյ�ǰ����
        m_db.close();

        // ����һ����ʱ���ӣ����ӵ� MySQL ϵͳ���ݿ�
        QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL", "tempConnection");
        tempDb.setHostName(m_db.hostName());
        tempDb.setUserName(m_db.userName());
        tempDb.setPassword(m_db.password());
        tempDb.setDatabaseName("mysql"); // ���ӵ�ϵͳ���ݿ�

        if (!tempDb.open())
        {
            qDebug() << "Failed to connect to MySQL system database:" << tempDb.lastError().text();
            return false;
        }

        // ���������ݿ�
        QSqlQuery query(tempDb);
        if (!query.exec("CREATE DATABASE IF NOT EXISTS todo_db"))
        {
            qDebug() << "Failed to create database:" << query.lastError().text();
            tempDb.close();
            return false;
        }
        tempDb.close();

        // �Ƴ���ʱ����
        QSqlDatabase::removeDatabase("tempConnection");

        // ���³��������´��������ݿ�
        m_db.setDatabaseName("todo_db");
        if (!m_db.open())
        {
            qDebug() << "Failed to open newly created database:" << m_db.lastError().text();
            return false;
        }

        return createTables();
    }

    // �������󣬷���ʧ��
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
    // ʵ�����ݿⱸ���߼�
    return false;
}


