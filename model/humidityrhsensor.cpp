#include "humidityrhsensor.h"

namespace sensor{

humidityRHsensor::humidityRHsensor (
    const QString name,
    const QString description,
    const unsigned int range,
    const double minValue,
    const double maxValue,
    const double volume
    ) : humiditysensor(name, description, range, minValue, maxValue, volume)
{
    double minResult = (minValue/volume)/maxValue * 100;
    double maxResult = (maxValue/volume)/maxValue * 100;
    resultTable = new class table(false, 1, range, minResult, maxResult);
    resultTable->setCellMin(minResult);
    resultTable->setCellMax(maxResult);
    resultTable->setHeaderData(0, Qt::Vertical, "Umidità Relativa");

    connect(variableTable, &table::dataChanged, this, &humidityRHsensor::updateResultTable);
}

void humidityRHsensor::updateTable() {
    if (!variableTable || !resultTable)
        return;

    for (int i = 0; i <= variableTable->columnCount(); ++i) {
        double watermassRowValue = variableTable->data(variableTable->index(0, i)).toDouble();
        double RHRowValue = (watermassRowValue/volume)/maxValue * 100;
        resultTable->setData(resultTable->index(0, i), QVariant(RHRowValue)); //umidità RH = (watermas/volume)/maxSaturation * 100
    }
}



void humidityRHsensor::updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    // Verifica che i parametri siano validi
    if (!topLeft.isValid() || !bottomRight.isValid())
        return;

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        for (int col = topLeft.column(); col <= bottomRight.column(); ++col) {

            QVariant data = variableTable->data(variableTable->index(row, col));

            double multipliedData = (data.toDouble()/volume)/maxValue * 100;

            resultTable->setData(resultTable->index(row, col), QVariant(multipliedData));
        }
    }
}


sensor& humidityRHsensor::setMinValue(const double value){
    this->minValue = value;
    variableTable->setCellMin(value);
    int minResult = (minValue/volume)/maxValue * 100;
    resultTable->setCellMin(minResult);
    updateTable();
    emit minValueChanged(value);
    return *this;
}

sensor& humidityRHsensor::setMaxValue(const double value){
    this->maxValue = value;
    variableTable->setCellMax(value);
    double maxResult = (maxValue/volume)/maxValue * 100;
    resultTable->setCellMax(maxResult);
    updateTable();
    emit maxValueChanged(value);
    return *this;
}

void humidityRHsensor::accept(visitor* visitor)  {
    visitor->visit(this);
}

}
