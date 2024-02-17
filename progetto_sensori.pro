QT       += core gui
QT       += core gui charts
QT       += widgets
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/accelerometer.cpp \
    view/accelerometereditwidget.cpp \
    view/accelerometerwidget.cpp \
    view/addsensordialog.cpp \
    view/baseaccelerometerwidget.cpp \
    view/basehumiditysensorwidget.cpp \
    view/basesensorwidget.cpp \
    view/basetemperaturesensorwidget.cpp \
    view/chartvisitor.cpp \
    json/containertojson.cpp \
    view/humidityrheditwidget.cpp \
    model/humidityrhsensor.cpp \
    view/humidityrhwidget.cpp \
    model/humiditysensor.cpp \
    view/humiditysensoreditwidget.cpp \
    view/humiditysensorwidget.cpp \
    json/jsontocontainer.cpp \
    main.cpp \
    view/mainwindow.cpp \
    model/sensor.cpp \
    model/sensorcontainer.cpp \
    view/sensorsearchwidget.cpp \
    model/table.cpp \
    view/temperatureceditwidget.cpp \
    model/temperaturecsensor.cpp \
    view/temperaturecwidget.cpp \
    model/temperaturesensor.cpp \
    view/temperaturesensoreditwidget.cpp \
    view/temperaturesensorwidget.cpp

HEADERS += \
    model/accelerometer.h \
    view/accelerometereditwidget.h \
    view/accelerometerwidget.h \
    view/addsensordialog.h \
    view/baseaccelerometerwidget.h \
    view/basehumiditysensorwidget.h \
    view/basesensorwidget.h \
    view/basetemperaturesensorwidget.h \
    view/chartvisitor.h \
    json/containertojson.h \
    view/humidityrheditwidget.h \
    model/humidityrhsensor.h \
    view/humidityrhwidget.h \
    model/humiditysensor.h \
    view/humiditysensoreditwidget.h \
    view/humiditysensorwidget.h \
    json/jsontocontainer.h \
    view/mainwindow.h \
    model/sensor.h \
    model/sensorcontainer.h \
    view/sensorsearchwidget.h \
    model/table.h \
    view/temperatureceditwidget.h \
    model/temperaturecsensor.h \
    view/temperaturecwidget.h \
    model/temperaturesensor.h \
    view/temperaturesensoreditwidget.h \
    view/temperaturesensorwidget.h
    visitor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
