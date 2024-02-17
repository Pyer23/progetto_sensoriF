#include "accelerometer.h"

namespace sensor{

accelerometer::accelerometer (
    const QString name,
    const QString description,
    const unsigned int range,
    const double minValue,
    const double maxValue,
    const double mass

    )
    : sensor(name, description, range, minValue, maxValue),
    mass(mass)
{
    variableTable = new class table(true, 1, range, minValue, maxValue);
    variableTable->setCellMin(minValue);
    variableTable->setCellMax(maxValue);
    variableTable->setHeaderData(0, Qt::Vertical, "Accelerazione");

    resultTable = new class table(false, 1, range, minValue*mass, maxValue*mass);
    resultTable->setCellMin(minValue*mass);
    resultTable->setCellMax(maxValue*mass);
    resultTable->setHeaderData(0, Qt::Vertical, "Forza");

    connect(variableTable, &table::dataChanged, this, &accelerometer::updateResultTable);
}

double accelerometer::getMass() const {
    return mass;
}

void accelerometer::updateTable() {
    if (!variableTable || !resultTable)
        return;

    for (int i = 0; i <= variableTable->columnCount(); ++i) {
        int accelerationTableValue = variableTable->data(variableTable->index(0, i)).toDouble();
        resultTable->setData(resultTable->index(0, i), QVariant(accelerationTableValue * mass));
    }
}

void accelerometer::updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    if (!topLeft.isValid() || !bottomRight.isValid())
        return;

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        for (int col = topLeft.column(); col <= bottomRight.column(); ++col) {
            QVariant data = variableTable->data(variableTable->index(row, col));

            double multipliedData = data.toDouble() * mass;

            resultTable->setData(resultTable->index(row, col), QVariant(multipliedData));
        }
    }    
}

sensor& accelerometer::setMinValue(const double value){
    this->minValue = value;
    variableTable->setCellMin(value);
    resultTable->setCellMin(value*mass);
    updateTable();
    emit minValueChanged(value);
    return *this;
}

sensor& accelerometer::setMaxValue(const double value){
    this->maxValue = value;
    variableTable->setCellMax(value);
    resultTable->setCellMax(value*mass);
    updateTable();
    emit maxValueChanged(value);
    return *this;
}

accelerometer& accelerometer::setMass(const double newMass) {
    this->mass = newMass;
    resultTable->setCellMin(minValue*mass);
    resultTable->setCellMax(maxValue*mass);
    updateTable();
    emit massChanged(newMass);
    return *this;
}

void accelerometer::accept(visitor* visitor)  {
    visitor->visit(this);
}

}
