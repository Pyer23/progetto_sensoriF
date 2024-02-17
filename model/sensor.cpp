#include "sensor.h"

namespace sensor{

sensor::sensor(
               const QString name,
               const QString description,
               const unsigned int range,
               const double minValue,
               const double maxValue)
    :
    name(name),
    description(description),
    range(range),
    minValue(minValue),
    maxValue(maxValue),
    variableTable(nullptr),
    resultTable(nullptr)
{
}

sensor::~sensor(){
}

QString sensor::getName() const{
    return name;
}

QString sensor::getDescription() const{
    return description;
}

unsigned int sensor::getRange() const{
    return range;
}

class table* sensor::getVariableTable() const{
    return variableTable;
}

class table* sensor::getResultTable() const{
    return resultTable;
}

double sensor::getMinValue() const{
    return minValue;
}

double sensor::getMaxValue() const{
    return maxValue;
}

void sensor::updateRange(){
    if (variableTable) {
        int currentColumnCount = variableTable->columnCount();
        int targetColumnCount = range;
        if (targetColumnCount >= 101 || targetColumnCount <= 1){
            return;
        }else{
            if (targetColumnCount > currentColumnCount) {
                variableTable->insertColumns(currentColumnCount, targetColumnCount - currentColumnCount);
                if(resultTable){
                    resultTable->insertColumns(currentColumnCount, targetColumnCount - currentColumnCount);
                }
            }
            else if (targetColumnCount < currentColumnCount) {
                variableTable->removeColumns(targetColumnCount, currentColumnCount - targetColumnCount);
                if(resultTable){
                    resultTable->removeColumns(targetColumnCount, currentColumnCount - targetColumnCount);
                }
            }
        }
    }
}

void sensor::increaseRange(const unsigned int increment) {
    if(range >= 100) {
        return;
    } else if (increment > 0) {
        range += increment;
        updateRange();
    }
}
void sensor::decreaseRange(const unsigned int decrement) {
    if (range <= 2) {
        return;
    } else if (decrement > 0 && decrement <= range && range >= 2) {
        range -= decrement;
        updateRange();
    }
}

sensor& sensor::setName(const QString newName){
    this->name = newName;
    emit nameChanged(newName);
    return *this;
}

sensor& sensor::setDescription(const QString newDescription){
    this->description = newDescription;
    emit descriptionChanged(newDescription);
    return *this;
}

}
