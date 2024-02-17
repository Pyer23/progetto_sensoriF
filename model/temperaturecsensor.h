#ifndef TEMPERATURECSENSOR_H
#define TEMPERATURECSENSOR_H

#include "temperaturesensor.h"

namespace sensor{

class temperatureCsensor: public temperaturesensor
{
    Q_OBJECT
private:
    double resistance;

public:
    temperatureCsensor(
        const QString name,
        const QString description,
        const unsigned int range,
        const double minValue,
        const double maxValue,
        const double resistance
        );

    virtual double getResistance() const;

    temperatureCsensor& setResistance(const double newResistance);

    void updateTable() override;
    void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) override;
    void accept(visitor* visitor) override;

    virtual sensor& setMinValue(const double value) override;
    virtual sensor& setMaxValue(const double value) override;

signals:
    void resistanceChanged(const double &newResistance);
};

}

#endif // TEMPERATURECSENSOR_H
