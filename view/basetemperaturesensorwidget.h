#ifndef BASETEMPERATURESENSORWIDGET_H
#define BASETEMPERATURESENSORWIDGET_H

#include "basesensorwidget.h"

namespace sensor {

class BaseTemperatureSensorWidget : public BaseSensorWidget
{
    Q_OBJECT
public:
    explicit BaseTemperatureSensorWidget(QWidget *parent = nullptr);

protected:
    QLabel *resistanceLabel;

    void updateResistanceLabel(const double &resistance);
};

}

#endif // BASETEMPERATURESENSORWIDGET_H
