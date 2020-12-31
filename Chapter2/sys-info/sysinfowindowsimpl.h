#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include <QtGlobal>
#include <QVector>

#include "sysinfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl : public SysInfo
{
public:
    SysInfoWindowsImpl();
    ~SysInfoWindowsImpl();

    // SysInfo interface
public:
    void init();
    [[nodiscard]] double cpuLoadAverage();
    [[nodiscard]] double memoryUsed();

private:
    [[nodiscard]] QVector<qulonglong> cpuRawData();
    [[nodiscard]] qulonglong convertFileTime(const FILETIME& filetime) const;

private:
    QVector<qulonglong> m_CpuLoadLastValues;
};

#endif // SYSINFOWINDOWSIMPL_H
