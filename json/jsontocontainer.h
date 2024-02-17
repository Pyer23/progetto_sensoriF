#ifndef JSONTOCONTAINER_H
#define JSONTOCONTAINER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>

#include "../model/sensorcontainer.h"

namespace sensor {

class JsonToContainer
{
public:
    SensorContainer convertJsonToContainer(const QString& jsonFilePath);

    QJsonObject loadFromJsonFile(const QString& filePath);

};

}

#endif // JSONTOCONTAINER_H
