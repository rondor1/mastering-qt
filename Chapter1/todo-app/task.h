#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString& name, QWidget *parent = nullptr);
    ~Task();

    void setName(const QString& name);
    QString name() const;
    bool isCompleted() const;

signals:
    void removed(Task* task);
    void statusChanged(Task* task);

private slots:
    void rename();
    void checked(bool isChecked);
private:
    Ui::Task *ui;
};

#endif // TASK_H
