#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Task;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void removeTask(Task* task);
    void taskStatusChanged(bool isChanged);

private:
    void updateStatus();

private:
    Ui::MainWindow *ui;
    QVector<Task*> m_taskList;
};
#endif // MAINWINDOW_H
