#include "MainWindow.h"
#include <QInputDialog> // Ensure this header is included for QInputDialog
#include <QLineEdit>    // Ensure this header is included for QLineEdit
#include <QMessageBox>

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

void MainWindow::on_addButton_clicked()
{
    bool ok;
    QString title = QInputDialog::getText(this, "Add Task", "Title:", QLineEdit::Normal, "", &ok);
    if (ok && !title.isEmpty())
    {
        Task task(-1, title, "", Task::Medium, QDate(), false);
        if (taskModel->addTask(task))
        {
            QMessageBox::information(this, "Success", "Task added successfully.");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to add task.");
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = taskTableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int taskId = taskModel->data(taskModel->index(selectedRows.first().row(), TaskModel::IdColumn)).toInt();
        if (taskModel->deleteTask(taskId))
        {
            QMessageBox::information(this, "Success", "Task deleted successfully.");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to delete task.");
        }
    }
}

void MainWindow::on_updateButton_clicked()
{
    QModelIndexList selectedRows = taskTableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int taskId = taskModel->data(taskModel->index(selectedRows.first().row(), TaskModel::IdColumn)).toInt();
        bool ok;
        QString title = QInputDialog::getText(this, "Update Task", "Title:", QLineEdit::Normal,
            taskModel->data(taskModel->index(selectedRows.first().row(), TaskModel::TitleColumn)).toString(), &ok);
        if (ok && !title.isEmpty())
        {
            Task task(taskId, title, "", Task::Medium, QDate(), false);
            if (taskModel->updateTask(task))
            {
                QMessageBox::information(this, "Success", "Task updated successfully.");
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to update task.");
            }
        }
    }
}

void MainWindow::on_searchButton_clicked()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, "Search Task", "Search:", QLineEdit::Normal, "", &ok);
    if (ok)
    {
        taskModel->setSearchText(searchText);
    }
}
