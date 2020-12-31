#include "sysinfo.h"
#include <QtGlobal>

#ifdef Q_OS_WIN
#include "sysinfowindowsimpl.h"
#elif defined(Q_OS_MAC)
//implement the MAC OS version
#elif defined(Q_OS_LINUX)
//implement the LINUX OS version
#endif
SysInfo::SysInfo()
{

}


SysInfo &SysInfo::instance()
{
#ifdef Q_OS_WIN
    static SysInfoWindowsImpl singleton;
#elif defined(Q_OS_MAC)
    //implement the MAC OS version
#elif defined(Q_OS_LINUX)
    //implement the LINUX OS version
#endif

    return singleton;
}

SysInfo::~SysInfo()
{

}
