#include "containertojson.h"

#include "../model/accelerometer.h"
#include "../model/humidityrhsensor.h"
#include "../model/humiditysensor.h"
#include "../model/temperaturecsensor.h"
#include "../model/temperaturesensor.h"

namespace sensor {

void ContainerToJson::saveToJson(const SensorContainer& container, const QString& filePath) {
    QJsonArray sensorsArray;
    std::vector<sensor*> sensors = container.getSensors();

    for (sensor* s : sensors) {
        QJsonObject sensorObject;
        sensorObject["name"] = s->getName();
        sensorObject["description"] = s->getDescription();
        sensorObject["range"] = QJsonValue(static_cast<int>(s->getRange()));
        sensorObject["minValue"] = s->getMinValue();
        sensorObject["maxValue"] = s->getMaxValue();

        if (accelerometer* accSensor = dynamic_cast<accelerometer*>(s)) {
            sensorObject["type"] = "accelerometer";
            sensorObject["mass"] = accSensor->getMass();
        }
        if (humiditysensor* humSensor = dynamic_cast<humiditysensor*>(s)) {
            if (humidityRHsensor* humRHSensor = dynamic_cast<humidityRHsensor*>(s)) {
                sensorObject["type"] = "humidityRH";
                sensorObject["volume"] = humRHSensor->getVolume();
            }else{
                sensorObject["type"] = "humidity";
                sensorObject["volume"] = humSensor->getVolume();
            }
        }
        if (temperaturesensor* tempSensor = dynamic_cast<temperaturesensor*>(s)) {
            if (temperatureCsensor* tempCSensor = dynamic_cast<temperatureCsensor*>(s)) {
                sensorObject["type"] = "temperatureC";
                sensorObject["volume"] = tempCSensor->getResistance();
            }else{
                Q_UNUSED(tempSensor)
                sensorObject["type"] = "temperature";
            }
        }

        sensorsArray.append(sensorObject);
    }

    QJsonObject mainObject;
    mainObject["sensors"] = sensorsArray;

    QJsonDocument jsonDocument(mainObject);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        //qDebug() << "Impossibile aprire il file" << filePath << "per la scrittura";
        return;
    }

    file.write(jsonDocument.toJson());
    file.close();
}

}
