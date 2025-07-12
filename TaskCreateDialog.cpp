#include "TaskCreateDialog.h"
#include <QMessageBox>

TaskCreateDialog::TaskCreateDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    // 信号连接
    connect(ui.saveBtn, &QPushButton::clicked, this, &TaskCreateDialog::onSaveClicked);
    connect(ui.cancelBtn, &QPushButton::clicked, this, &TaskCreateDialog::onCancelClicked);
}

void TaskCreateDialog::onSaveClicked()
{
    if (ui.titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题不能为空。");
        return;
    }

    Task task = getTask();
    emit taskCreated(task); // 发出信号
    accept(); // 关闭对话框
}

void TaskCreateDialog::onCancelClicked()
{
    reject(); // 关闭对话框并设置结果为 Rejected
}

Task TaskCreateDialog::getTask() const
{
    Task task;
    task.setTitle(ui.titleEdit->text());
    task.setDescription(ui.descEdit->toPlainText());
    if (ui.lowRadio->isChecked())
        task.setPriority(Task::Low);
    else if (ui.mediumRadio->isChecked())
        task.setPriority(Task::Medium);
    else
        task.setPriority(Task::High);

    task.setDueDate(ui.dateEdit->date());
    task.setCompleted(ui.completedCheck->isChecked());
    return task;
}

void TaskCreateDialog::setTask(const Task& task)
{
    ui.titleEdit->setText(task.title());
    ui.descEdit->setPlainText(task.description());

    switch (task.priority()) {
    case Task::Low:
        ui.lowRadio->setChecked(true);
        break;
    case Task::Medium:
        ui.mediumRadio->setChecked(true);
        break;
    case Task::High:
        ui.highRadio->setChecked(true);
        break;
    }

    ui.dateEdit->setDate(task.dueDate().isValid() ? task.dueDate() : QDate::currentDate());
    ui.completedCheck->setChecked(task.completed());
}

