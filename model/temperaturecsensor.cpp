#include "temperaturecsensor.h"

namespace sensor{

temperatureCsensor::temperatureCsensor (
    const QString name,
    const QString description,
    const unsigned int range,
    const double minValue,
    const double maxValue,
    const double resistance
    ) : temperaturesensor(name, description, range, minValue, maxValue),
    resistance(resistance)
{
    variableTable = new class table(true, 1, range, minValue, maxValue);
    variableTable->setHeaderData(0, Qt::Vertical, "Temperatura");
    variableTable->setCellMin(minValue);
    variableTable->setCellMax(maxValue);

    resultTable = new class table(false, 1, range, minValue/resistance, maxValue/resistance);
    resultTable->setCellMin(minValue/resistance);
    resultTable->setCellMax(maxValue/resistance);
    resultTable->setHeaderData(0, Qt::Vertical, "Temperatura a contatto");

    connect(variableTable, &table::dataChanged, this, &temperaturesensor::updateResultTable);
}

double temperatureCsensor::getResistance() const {
    return resistance;
}

void temperatureCsensor::updateTable() {
    if (!variableTable || !resultTable)
        return;

    for (int i = 0; i <= variableTable->columnCount(); ++i) {
        double temperatureRowValue = variableTable->data(variableTable->index(0, i)).toDouble();
        resultTable->setData(resultTable->index(0, i), QVariant(temperatureRowValue/resistance));  //temperatura = temperatura/resistenza (CONTATTO)
    }
}

void temperatureCsensor::updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    // Verifica che i parametri siano validi
    if (!topLeft.isValid() || !bottomRight.isValid())
        return;

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        for (int col = topLeft.column(); col <= bottomRight.column(); ++col) {
            QVariant data = variableTable->data(variableTable->index(row, col));

            double multipliedData = data.toDouble() / resistance;

            resultTable->setData(resultTable->index(row, col), QVariant(multipliedData));
        }
    }
}

sensor& temperatureCsensor::setMinValue(const double value){
    this->minValue = value;
    variableTable->setCellMin(value);
    resultTable->setCellMin(value/resistance);
    updateTable();
    emit minValueChanged(value);
    return *this;
}

sensor& temperatureCsensor::setMaxValue(const double value){
    this->maxValue = value;
    variableTable->setCellMax(value);
    resultTable->setCellMax(value/resistance);
    updateTable();
    emit maxValueChanged(value);
    return *this;
}

temperatureCsensor& temperatureCsensor::setResistance(const double newResistance){
    this->resistance = newResistance;
    resultTable->setCellMin(minValue/resistance);
    resultTable->setCellMax(maxValue/resistance);
    updateTable();
    emit resistanceChanged(newResistance);
    return *this;
}

void temperatureCsensor::accept(visitor* visitor)  {
    visitor->visit(this);
}

}
