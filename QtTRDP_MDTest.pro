QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    historydialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    paramdialog.cpp \
    selectdialog.cpp \
    videodialog.cpp

HEADERS += \
    historydialog.h \
    include/iec61375-2-3.h \
    include/tau_ctrl.h \
    include/tau_ctrl_types.h \
    include/tau_dnr.h \
    include/tau_dnr_types.h \
    include/tau_marshall.h \
    include/tau_so_if.h \
    include/tau_tti.h \
    include/tau_tti_types.h \
    include/tau_xml.h \
    include/trdp_if_light.h \
    include/trdp_serviceRegistry.h \
    include/trdp_tsn_def.h \
    include/trdp_types.h \
    include/vos_mem.h \
    include/vos_shared_mem.h \
    include/vos_sock.h \
    include/vos_thread.h \
    include/vos_types.h \
    include/vos_utils.h \
    logindialog.h \
    mainwindow.h \
    myStruct.h \
    paramdialog.h \
    selectdialog.h \
    trdpStruct.h \
    videodialog.h

FORMS += \
    historydialog.ui \
    logindialog.ui \
    mainwindow.ui \
    paramdialog.ui \
    selectdialog.ui \
    videodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    include/trdp-config.xsd \
    lib/TRDP.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lTRDP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lTRDPd

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

INCLUDEPATH += \
        D:\Programs\opencv\build\include\opencv2  \
        D:\Programs\opencv\build\include

LIBS += D:\Programs\opencv\build\x64\vc15\lib\opencv_world450.lib


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libTRDP.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libTRDPd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/TRDP.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/TRDPd.lib

#win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/TRDP.lib

RESOURCES +=
