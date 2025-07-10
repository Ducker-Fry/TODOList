#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include"DatabaseManager.h"
#include<qdebug.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();
    // ��ʼ�����ݿ�
    if (!DatabaseManager::instance().initDatabase())
    {
        qDebug() << "Failed to initialize database.";
        return -1;
    }

    qDebug() << "Database initialized successfully.";
    MainWindow window;
    window.show();
    return app.exec();
}
