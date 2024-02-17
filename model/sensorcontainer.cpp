#include "sensorcontainer.h"

namespace sensor {

void SensorContainer::addSensor(sensor* sensor) {
    sensors.push_back(sensor);
}

std::vector<sensor*> SensorContainer::getSensors() const {
    return sensors;
}

std::vector<sensor*> SensorContainer::findSensorsByName(const QString& name) {
    std::vector<sensor*> foundSensors;
    if (name.isEmpty()) {
        return foundSensors;
    }
    QString lowerName = name.toLower();
    for (sensor* s : sensors) {
        QString sensorName = s->getName().toLower();
        if (sensorName.contains(lowerName)) {
            foundSensors.push_back(s);
        }
    }
    return foundSensors;
}

int SensorContainer::size(){
    return sensors.size();
}

sensor* SensorContainer::sensorAt(int index){
    return sensors[index];
}

void SensorContainer::clear(){
    sensors.clear();
}

void SensorContainer::removeSensor(sensor* s) {
    auto it = std::find(sensors.begin(), sensors.end(), s);
    if (it != sensors.end()) {
        sensors.erase(it);
    }
}

}
