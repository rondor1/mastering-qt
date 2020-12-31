#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "sysinfo.h"
#include <QVector>
#include <QtGlobal>

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    // SysInfo interface
public:
    void init();
    double cpuLoadAverage();
    double memoryUsed();

private:
    QVector<qulonglong> cpuRawData();

private:
    QVector<qulonglong> m_CpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
