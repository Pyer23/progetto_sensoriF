#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "sensor.h"

namespace sensor{

class accelerometer: public sensor
{
    Q_OBJECT
private:
    double mass;
public:
    accelerometer(
        const QString name,
        const QString description,
        const unsigned int range,
        const double minValue,
        const double maxValue,
        const double mass
        );

    virtual double getMass() const;

    accelerometer& setMass(const double newMass);

    void updateTable() override;

    void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) override;

    void accept(visitor* visitor) override;

    virtual sensor& setMinValue(const double value) override;
    virtual sensor& setMaxValue(const double value) override;

signals:
    void massChanged(const double &newMass);

};

}

#endif // ACCELEROMETER_H
