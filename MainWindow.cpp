#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    taskModel = new TaskModel(this);
    taskTableView = new QTableView(this);
    taskTableView->setModel(taskModel);

    setCentralWidget(taskTableView);
}

MainWindow::~MainWindow()
{}

