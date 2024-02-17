#include "humiditysensor.h"

namespace sensor{

humiditysensor::humiditysensor (
    const QString name,
    const QString description,
    const unsigned int range,
    const double minValue,
    const double maxValue,
    const double volume
    ) : sensor(name, description, range, minValue, maxValue),
    volume(volume)
{
    variableTable = new class table(true, 1, range, minValue, maxValue);
    variableTable->setCellMin(minValue);
    variableTable->setCellMax(maxValue);
    variableTable->setHeaderData(0, Qt::Vertical, "Vapore Acqueo");

    resultTable = new class table(false, 1, range, minValue/volume, maxValue/volume);
    resultTable->setCellMin(minValue/volume);
    resultTable->setCellMax(maxValue/volume);
    resultTable->setHeaderData(0, Qt::Vertical, "Umidità Assoluta");

    connect(variableTable, &table::dataChanged, this, &humiditysensor::updateResultTable);
}

double humiditysensor::getVolume() const {
    return volume;
}

void humiditysensor::updateTable() {
    if (!variableTable || !resultTable)
        return;

    for (int i = 0; i <= variableTable->columnCount(); ++i) {
        double watermassRowValue = variableTable->data(variableTable->index(0, i)).toDouble();
        resultTable->setData(resultTable->index(0, i), QVariant(watermassRowValue/volume));  //umidità AH = watermass/volume
    }

}

void humiditysensor::updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    if (!topLeft.isValid() || !bottomRight.isValid())
        return;

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        for (int col = topLeft.column(); col <= bottomRight.column(); ++col) {

            QVariant data = variableTable->data(variableTable->index(row, col));

            double multipliedData = data.toDouble() / volume;
            resultTable->setData(resultTable->index(row, col), QVariant(multipliedData));
        }
    }
}

sensor& humiditysensor::setMinValue(const double value){
    this->minValue = value;
    variableTable->setCellMin(value);
    resultTable->setCellMin(value/volume);
    updateTable();
    emit minValueChanged(value);
    return *this;
}

sensor& humiditysensor::setMaxValue(const double value){
    this->maxValue = value;
    variableTable->setCellMax(value);
    resultTable->setCellMax(value/volume);
    updateTable();
    emit maxValueChanged(value);
    return *this;
}

humiditysensor& humiditysensor::setVolume(const double newVolume) {
    this->volume = newVolume;
    resultTable->setCellMin(minValue/volume);
    resultTable->setCellMax(maxValue/volume);
    updateTable();
    emit volumeChanged(newVolume);
    return *this;
}

void humiditysensor::accept(visitor* visitor)  {
    visitor->visit(this);
}

}
