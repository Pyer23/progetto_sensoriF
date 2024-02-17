#ifndef HUMIDITYRHSENSOR_H
#define HUMIDITYRHSENSOR_H

#include "humiditysensor.h"

namespace sensor{

class humidityRHsensor: public humiditysensor
{
    Q_OBJECT
public:
    humidityRHsensor(
        const QString name,
        const QString description,
        const unsigned int range,
        const double minValue,
        const double maxValue,
        const double volume
        );

    void updateTable() override;
    void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) override;

    void accept(visitor* visitor) override;

    virtual sensor& setMinValue(const double value) override;
    virtual sensor& setMaxValue(const double value) override;
};

}

#endif // HUMIDITYRHSENSOR_H
