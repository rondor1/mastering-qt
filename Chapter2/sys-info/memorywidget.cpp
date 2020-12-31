#include "memorywidget.h"
#include <QtCharts/QAreaSeries>
using namespace QtCharts;

constexpr int CHART_X_RANGE_COUNT=50;
constexpr int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
constexpr int COLOR_DARK_BLUE = 0x209fdf;
constexpr int COLOR_LIGHT_BLUE = 0xbfdfef;
constexpr int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget* parent) : SysInfoWidget(parent), m_lineSeries(new QLineSeries(this)), m_PointPositionX(0)
{

    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    //Create a line series which should handle the data representation
    QAreaSeries* areaSeries = new QAreaSeries(m_lineSeries);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);


    QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory used");
    chart->createDefaultAxes();
    chart->axisX()->setVisible(false);
    chart->axisX()->setRange(0, CHART_X_RANGE_MAX);
    chart->axisY()->setRange(0, 100);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = SysInfo::instance().memoryUsed();
    m_lineSeries->append(m_PointPositionX++, memoryUsed);
    if(m_lineSeries->count() > CHART_X_RANGE_COUNT)
    {
        QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX,0);
        m_lineSeries->remove(0);
    }

}

