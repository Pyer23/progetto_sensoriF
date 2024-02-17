#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "sensor.h"

namespace sensor{

class humiditysensor: public sensor
{
    Q_OBJECT
protected:
    double volume;

public:
    humiditysensor(
        const QString name,
        const QString description,
        const unsigned int range,
        const double minValue,
        const double maxValue,
        const double volume
        );

    virtual double getVolume() const;

    humiditysensor &setVolume(const double newVolume);

    void updateTable() override;
    void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) override;

    void accept(visitor* visitor) override;

    virtual sensor& setMinValue(const double value) override;
    virtual sensor& setMaxValue(const double value) override;

signals:
    void volumeChanged(const double &newVolume);
};

}

#endif // HUMIDITYSENSOR_H
