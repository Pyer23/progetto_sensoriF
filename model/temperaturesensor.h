#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "sensor.h"

namespace sensor{

class temperaturesensor: public sensor
{
    Q_OBJECT

public:
    temperaturesensor(
        const QString name,
        const QString description,
        const unsigned int range,
        const double minValue,
        const double maxValue
        );

    void updateTable() override;
    void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) override;
    void accept(visitor* visitor) override;

    virtual sensor& setMinValue(const double value) override;
    virtual sensor& setMaxValue(const double value) override;
};

}

#endif // TEMPERATURESENSOR_H

