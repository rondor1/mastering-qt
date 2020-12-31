#include "task.h"
#include "ui_task.h"

#include <QInputDialog>

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    connect(ui->editButton, &QAbstractButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QAbstractButton::clicked, this,
            [this]()->void{emit removed(this);});
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name() const
{
    return ui->checkbox->text();
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

void Task::rename()
{
    bool isRenameOk = false;
    auto nameChange = QInputDialog::getText(this, tr("Edit task"),
                                            tr("Task name"),
                                            QLineEdit::Normal,
                                            this->name(),
                                            &isRenameOk);

    if(isRenameOk && !nameChange.isEmpty())
    {
        setName(nameChange);
    }
}

void Task::checked(bool isChecked)
{
    QFont newFont(ui->checkbox->font());
    newFont.setStrikeOut(isChecked);
    ui->checkbox->setFont(newFont);
    emit statusChanged(this);
}

Task::~Task()
{
    delete ui;
}
