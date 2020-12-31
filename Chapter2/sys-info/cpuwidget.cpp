#include "cpuwidget.h"

#include "sysinfo.h"

using namespace QtCharts;

CpuWidget::CpuWidget(QWidget *parent) : SysInfoWidget(parent),
    m_pieSeries(new QPieSeries(this))
{
    //Create a series which should handle data presentation
    m_pieSeries->setHoleSize(0.35);
    m_pieSeries->append("CPU Load", 30.0);
    m_pieSeries->append("CPU Free", 70.0);

    //Add it to the chart, which should be ready for presentation
    QChart* chart = chartView().chart();
    chart->addSeries(m_pieSeries);
    chart->setTitle("CPU Average load");
}

void CpuWidget::updateSeries()
{
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();
    m_pieSeries->clear();
    m_pieSeries->append("Load", cpuLoadAverage);
    m_pieSeries->append("Free", 100.0 - cpuLoadAverage);
}
