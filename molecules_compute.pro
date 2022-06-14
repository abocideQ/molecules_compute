QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    main.cpp \
    mainwindow.cpp \
    qclickqlabel.cpp \
    qcustomplot.cpp \
    brigde.cpp \
    core/ParseX.cpp \
    core/ParseA.cpp \
    core/MergeXA.cpp \
    core/ComputeQevj.cpp \
    core/ComputeQ.cpp \
#    core/XYModel.cpp \
#    core/FileUtils.cpp \
#    core/FileWriter.cpp \
#    core/DecimalUtils.cpp \
    core/LongDouble.cpp \
#    gmp/gmp.cpp \

HEADERS += \
    mainwindow.h \
    qclickqlabel.h \
    qcustomplot.h \
    brigde.h \
    core/ParseX.h \
    core/ParseA.h \
    core/MergeXA.h \
    core/ComputeQevj.h \
    core/ComputeQ.h \
    core/XYModel.h \
    core/FileUtils.h \
    core/FileWriter.h \
    core/DecimalUtils.h \
    core/LongDouble.h \
    gmp/gmp.h \

FORMS += \
    mainwindow.ui \

LIBS += \
    -L$$PWD/gmp/ -llibgmp-10 \
#LIBS += -llibgmp-10
#win32: LIBS += -L$$PWD/ -llibgmp-10
#INCLUDEPATH += $$PWD/
#DEPENDPATH += $$PWD/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
