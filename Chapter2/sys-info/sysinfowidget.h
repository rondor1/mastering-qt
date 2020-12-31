#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include "sysinfo.h"


class SysInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SysInfoWidget(QWidget *parent = nullptr,
                           int startDelayMs = 500,
                           int updateSeriesDelayMs = 500);

protected:
    [[nodiscard]] QtCharts::QChartView& chartView();

protected slots:
    virtual void updateSeries() = 0;


private:
    QTimer m_refreshTimer;
    QtCharts::QChartView m_chartView;

};

#endif // SYSINFOWIDGET_H
