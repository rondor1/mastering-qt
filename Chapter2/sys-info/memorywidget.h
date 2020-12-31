#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "sysinfowidget.h"

#include <QtCharts/QLineSeries>

class MemoryWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    MemoryWidget(QWidget* parent = nullptr);

protected slots:
    void updateSeries();
private:
    QtCharts::QLineSeries* m_lineSeries;
    qint64 m_PointPositionX;
};

#endif // MEMORYWIDGET_H
