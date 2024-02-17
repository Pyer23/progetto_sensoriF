#ifndef CONTAINERTOJSON_H
#define CONTAINERTOJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "../model/sensorcontainer.h"

namespace sensor {

class ContainerToJson {

public:
    void saveToJson(const SensorContainer& container, const QString& filePath);
};

}
#endif // CONTAINERTOJSON_H
