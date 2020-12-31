#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cpuwidget.h"
#include <QLineEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_cpuWidget(this), m_memoryWidget(this)
{
    ui->setupUi(this);
    SysInfo::instance().init();
    ui->centralwidget->layout()->addWidget(&m_cpuWidget);
    ui->centralwidget->layout()->addWidget(&m_memoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

