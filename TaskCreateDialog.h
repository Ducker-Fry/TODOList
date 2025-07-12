#pragma once

#include <QDialog>
#include <QDate>
#include "ui_TaskCreateDialog.h"
#include "Task.h"

class TaskCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskCreateDialog(QWidget *parent = nullptr);
    Task getTask() const;
    void setTask(const Task& task);

signals:
    void taskCreated(const Task& task);

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Ui::TaskCreateDialog ui;
};
