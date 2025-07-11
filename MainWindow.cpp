#include "MainWindow.h"
#include <QInputDialog> // Ensure this header is included for QInputDialog
#include <QLineEdit>    // Ensure this header is included for QLineEdit
#include <QMessageBox>
#include<qlayout.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect_signal_slot();

    // 初始化任务模型和视图
    taskModel = new TaskModel(this);
    StatisticsManager* statisticsManager = new StatisticsManager(taskModel, this);
    ui.tableView->setModel(taskModel);
    ui.statistical_chart->setStatisticsManager(statisticsManager);
    // 初始化筛选控件
    initFilters();
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

void MainWindow::connect_signal_slot()
{
    connect(ui.addTask_button, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);

    connect(ui.updateList_button, &QPushButton::clicked, this, &MainWindow::on_updateButton_clicked);

    connect(ui.filterButton, &QPushButton::clicked, this, &MainWindow::on_filterButton_clicked);
    connect(ui.searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui.priorityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::on_priorityComboBox_currentIndexChanged);

    connect(ui.showCompletedCheckBox, &QCheckBox::setCheckState,
        this, &MainWindow::on_showCompletedCheckBox_stateChanged);
    connect(ui.showOverdueCheckBox, &QCheckBox::setCheckState,
        this, &MainWindow::on_showOverdueCheckBox_stateChanged);
    connect(ui.startDateEdit, &QDateEdit::dateChanged,
        this, &MainWindow::on_startDateEdit_dateChanged);
    connect(ui.endDateEdit, &QDateEdit::dateChanged,
        this, &MainWindow::on_endDateEdit_dateChanged);
}

void MainWindow::initFilters() {
    // 初始化优先级下拉框
    ui.priorityComboBox->addItem("All Priorities", -1);
    ui.priorityComboBox->addItem("Low", Task::Low);
    ui.priorityComboBox->addItem("Medium", Task::Medium);
    ui.priorityComboBox->addItem("High", Task::High);
    
    // 初始化日期范围
    ui.startDateEdit->setDate(QDate::currentDate());
    ui.endDateEdit->setDate(QDate::currentDate().addDays(7));
}

void MainWindow::on_filterButton_clicked() {
    bool showCompleted = ui.showCompletedCheckBox->isChecked();
    bool showOverdue = ui.showOverdueCheckBox->isChecked();
    int priorityIndex = ui.priorityComboBox->currentData().toInt();
    Task::Priority priority = (priorityIndex >= 0) ? static_cast<Task::Priority>(priorityIndex) : Task::Low;
    QDate startDate = ui.startDateEdit->date();
    QDate endDate = ui.endDateEdit->date();
    
    taskModel->setFilterByStatus(showCompleted, showOverdue);
    taskModel->setFilterByPriority(priority);
    taskModel->setFilterByDateRange(startDate, endDate);
}

void MainWindow::on_searchButton_clicked() {
    QString searchText = ui.searchLineEdit->text();
    taskModel->setSearchText(searchText);
}

void MainWindow::on_priorityComboBox_currentIndexChanged(int index) {
    // 当优先级选择变化时立即应用过滤
    on_filterButton_clicked();
}

void MainWindow::on_showCompletedCheckBox_stateChanged(int state) {
    // 当完成状态选择变化时立即应用过滤
    on_filterButton_clicked();
}

void MainWindow::on_showOverdueCheckBox_stateChanged(int state) {
    // 当逾期状态选择变化时立即应用过滤
    on_filterButton_clicked();
}

void MainWindow::on_startDateEdit_dateChanged(const QDate &date) {
    // 当开始日期变化时立即应用过滤
    on_filterButton_clicked();
}

void MainWindow::on_endDateEdit_dateChanged(const QDate &date) {
    // 当结束日期变化时立即应用过滤
    on_filterButton_clicked();
}

