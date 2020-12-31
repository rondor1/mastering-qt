#include "sysinfowidget.h"

SysInfoWidget::SysInfoWidget(QWidget *parent, int startDelayMs,
                             int updateSeriesDelayMs) : QWidget(parent),m_chartView(this)
{
    //Set the timer triggering part
    m_refreshTimer.setInterval(updateSeriesDelayMs);
    connect(&m_refreshTimer, &QTimer::timeout, this, &SysInfoWidget::updateSeries);
    QTimer::singleShot(startDelayMs, [this]{m_refreshTimer.start();});

    m_chartView.setRenderHint(QPainter::Antialiasing);
    m_chartView.chart()->legend()->setVisible(false);

    //Create sys info box as a new layout
    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    layout()->addWidget(&m_chartView);
    setLayout(vBoxLayout);
}

QtCharts::QChartView &SysInfoWidget::chartView()
{
    return m_chartView;
}
