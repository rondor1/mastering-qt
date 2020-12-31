#include "sysinfowindowsimpl.h"

#include <windows.h>

SysInfoWindowsImpl::SysInfoWindowsImpl() : SysInfo()
{

}

void SysInfoWindowsImpl::init()
{
    m_CpuLoadLastValues = cpuRawData();
}

double SysInfoWindowsImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = m_CpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    m_CpuLoadLastValues = secondSample;

    qulonglong currentIdle = secondSample[0] - firstSample[0];
    qulonglong currentKernel = secondSample[1] - firstSample[1];
    qulonglong currentUser = secondSample[2] - firstSample[2];
    qulonglong currentSystem = currentKernel + currentUser;

    double percentage = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percentage, 100.0);
}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    qulonglong memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return (double)memoryPhysicalUsed / (double) memoryStatus.ullTotalPhys * 100.0;
}

QVector<qulonglong> SysInfoWindowsImpl::cpuRawData()
{
    FILETIME kernelTime;
    FILETIME idleTime;
    FILETIME userTime;
    QVector<qulonglong> rawData;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));

    return rawData;
}

qulonglong SysInfoWindowsImpl::convertFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;

    return largeInteger.QuadPart;
}

SysInfoWindowsImpl::~SysInfoWindowsImpl()
{

}

