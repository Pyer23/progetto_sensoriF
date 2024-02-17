#include "jsontocontainer.h"

#include "../model/accelerometer.h"
#include "../model/humidityrhsensor.h"
#include "../model/humiditysensor.h"
#include "../model/temperaturecsensor.h"
#include "../model/temperaturesensor.h"

namespace sensor {

SensorContainer JsonToContainer::convertJsonToContainer(const QString& jsonFilePath) {
    SensorContainer container;
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossibile aprire il file JSON per la lettura";
        return container;
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qDebug() << "Il documento JSON non contiene un oggetto JSON";
        return container;
    }

    QJsonObject mainObject = doc.object();
    if (!mainObject.contains("sensors")) {
        qDebug() << "Il documento JSON non contiene la chiave 'sensors'";
        return container;
    }

    QJsonArray sensorArray = mainObject["sensors"].toArray();
    for (const QJsonValue& sensorValue : sensorArray) {
        QJsonObject sensorObject = sensorValue.toObject();
        QString name = sensorObject["name"].toString();
        QString description = sensorObject["description"].toString();
        int range = sensorObject["range"].toInt();
        double minValue = sensorObject["minValue"].toDouble();
        double maxValue = sensorObject["maxValue"].toDouble();
        QString type = sensorObject["type"].toString(); // tipo di sensore

        //crazione dei sensori in base al tipo
        sensor* newSensor = nullptr;
        if (type == "accelerometer") {
            double mass = sensorObject["mass"].toDouble();
            newSensor = new accelerometer(name, description, range, minValue, maxValue, mass);
        } else if (type == "humidity") {
            double volume = sensorObject["volume"].toDouble();
            newSensor = new humiditysensor(name, description, range, minValue, maxValue, volume);
        } else if (type == "humidityRH") {
            double volume = sensorObject["volume"].toDouble();
            newSensor = new humidityRHsensor(name, description, range, minValue, maxValue, volume);
        } else if (type == "temperature") {
            newSensor = new temperaturesensor(name, description, range, minValue, maxValue);
        } else if (type == "temperatureC") {
            double resistance = sensorObject["volume"].toDouble();
            newSensor = new temperatureCsensor(name, description, range, minValue, maxValue, resistance);
        }

        if (newSensor != nullptr) {
            container.addSensor(newSensor);
        } else {
            //qDebug() << "Tipo di sensore non supportato: " << type;
        }
    }

    return container;
}

QJsonObject JsonToContainer::loadFromJsonFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile aprire il file JSON selezionato.");
        return QJsonObject();
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError) {
        QMessageBox::warning(nullptr, "Errore JSON", "Errore durante la conversione del file JSON selezionato.");
        return QJsonObject();
    }

    if (!doc.isObject()) {
        QMessageBox::warning(nullptr, "Errore JSON", "Il file JSON selezionato non contiene un oggetto JSON.");
        return QJsonObject();
    }

    return doc.object();
}

}
