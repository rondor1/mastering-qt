#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QtCharts/QPieSeries>

#include "sysinfowidget.h"

class CpuWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    CpuWidget(QWidget* parent = nullptr);

protected slots:
    void updateSeries();

private:
    QtCharts::QPieSeries* m_pieSeries;
};

#endif // CPUWIDGET_H
