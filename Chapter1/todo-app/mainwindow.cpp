#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    //Create a new task, add it to the list and display it in the main window
    bool inputIsOk = false;
    auto taskName = QInputDialog::getText(this, tr("Add task"), tr("Task name"), QLineEdit::Normal,
                                          tr("Untitled task"), &inputIsOk);
    if(inputIsOk && !taskName.isEmpty())
    {
        auto task = new Task(taskName,this);
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
        m_taskList.append(task);
        ui->taskLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    auto delTask = std::find_if(m_taskList.begin(), m_taskList.end(),
                               [task](auto taskIterator)->auto{return task == taskIterator;});

    if(delTask != std::end(m_taskList))
    {
        m_taskList.erase(delTask);
        ui->taskLayout->removeWidget(task);
        //Remove task's parent
        task->setParent(nullptr);
        delete task;
        updateStatus();
    }
}

void MainWindow::taskStatusChanged(bool isChanged)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount = 0;
    int leftToDo = 0;
    for(auto it : m_taskList)
    {
        if(it->isCompleted())
        {
            ++completedCount;
        }
    }

    leftToDo = m_taskList.size() - completedCount;

    ui->statusLabel->setText(QString("Status: %1 todo / %2 done").arg(leftToDo).arg(completedCount));
    update();
}
