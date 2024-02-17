#ifndef CHARTVISITOR_H
#define CHARTVISITOR_H

#include "../model/visitor.h"
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "accelerometerwidget.h"
#include "accelerometereditwidget.h"

#include "humiditysensorwidget.h"
#include "humiditysensoreditwidget.h"
#include "humidityrhwidget.h"
#include "humidityrheditwidget.h"

#include "temperaturesensorwidget.h"
#include "temperaturesensoreditwidget.h"
#include "temperaturecwidget.h"
#include "temperatureceditwidget.h"

namespace sensor {

class chartvisitor : public visitor, public QObject
{
private:
    QStackedWidget* stackedWidget;

public slots:
    void switchWidget();

public:
    void visit(accelerometer* accelerometer) override;

    void visit(humiditysensor* humiditysensor) override;
    void visit(humidityRHsensor* humidityRHsensor) override;

    void visit(temperaturesensor* temperaturesensor) override;
    void visit(temperatureCsensor* temperatureCsensor) override;

    QStackedWidget* getWidget() const;
};

}
#endif // CHARTVISITOR_H
