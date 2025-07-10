#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include"DatabaseManager.h"
#include<qdebug.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // 初始化数据库
    //if (!DatabaseManager::instance().initDatabase())
    //{
    //    qDebug() << "Failed to initialize database.";
    //    return -1;
    //}

// 检查可用的数据库驱动
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

    // 尝试加载MySQL驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("todo_db");
    db.setUserName("root");
    db.setPassword("112106120Sql@");

    if (!db.open())
    {
        qDebug() << "Failed to open database:" << db.lastError().text();
    }
    else
    {
        qDebug() << "Database opened successfully.";
    }
    MainWindow window;
    window.show();
    return app.exec();
}
