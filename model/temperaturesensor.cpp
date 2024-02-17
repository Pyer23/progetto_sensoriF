#include "temperaturesensor.h"

namespace sensor{

temperaturesensor::temperaturesensor (
    const QString name,
    const QString description,
    const unsigned int range,
    const double minValue,
    const double maxValue
    ) : sensor(name, description, range, minValue, maxValue)
{
    variableTable = new class table(true, 1, range, minValue, maxValue);
    variableTable->setHeaderData(0, Qt::Vertical, "Temperatura");
    variableTable->setCellMin(minValue);
    variableTable->setCellMax(maxValue);
}


void temperaturesensor::updateTable() {
    if (!variableTable)
        return;

    for (int i = 0; i <= variableTable->columnCount(); ++i) {
        double temperatureRowValue = variableTable->data(variableTable->index(0, i)).toDouble();
        variableTable->setData(variableTable->index(0, i), QVariant(temperatureRowValue));  //temperatura = temperatura (NO CONTATTO)
    }}


void temperaturesensor::updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    Q_UNUSED(topLeft)
    Q_UNUSED(bottomRight)
    return;
}

sensor& temperaturesensor::setMinValue(const double value){
    this->minValue = value;
    variableTable->setCellMin(value);
    updateTable();
    emit minValueChanged(value);
    return *this;
}

sensor& temperaturesensor::setMaxValue(const double value){
    this->maxValue = value;
    variableTable->setCellMax(value);
    updateTable();
    emit maxValueChanged(value);
    return *this;
}

void temperaturesensor::accept(visitor* visitor)  {
    visitor->visit(this);
}

}
