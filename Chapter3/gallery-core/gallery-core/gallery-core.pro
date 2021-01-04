QT -= gui
QT += sql

TEMPLATE = lib
DEFINES += GALLERYCORE_LIBRARY

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    albumdao.cpp \
    albummodel.cpp \
    databasemanager.cpp \
    gallerycore.cpp \
    picture.cpp \
    picturedao.cpp

HEADERS += \
    album.h \
    albumdao.h \
    albummodel.h \
    databasemanager.h \
    gallery-core_global.h \
    gallerycore.h \
    picture.h \
    picturedao.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
