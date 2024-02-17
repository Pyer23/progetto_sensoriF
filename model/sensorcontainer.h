#ifndef SENSORCONTAINER_H
#define SENSORCONTAINER_H

#include <vector>
#include <cctype>

#include <QString>

#include "sensor.h"

namespace sensor {

class SensorContainer {
private:
    std::vector<sensor*> sensors;

public:
    void addSensor(sensor* sensor);

    std::vector<sensor*> getSensors() const;

    std::vector<sensor*> findSensorsByName(const QString& name);

    int size();

    sensor* sensorAt(int index);

    void clear();

    void removeSensor(sensor* s);
};

} // namespace sensor


#endif // SENSORCONTAINER_H
