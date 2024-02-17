#ifndef SENSOR_H
#define SENSOR_H

#include "table.h"
#include "visitor.h"
#include <QString>
#include <QObject>

namespace sensor {

class sensor : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString description;

    unsigned int range;

protected:
    double minValue;
    double maxValue;

    table* variableTable;
    table* resultTable;

public:
    sensor(
           const QString name,
           const QString description,
           const unsigned int range,
           const double minValue,
           const double maxValue
           );

    virtual ~sensor();

    QString getName() const;
    QString getDescription() const;
    unsigned int getRange() const;
    class table* getVariableTable() const;
    class table* getResultTable() const;

    double getMinValue() const;
    double getMaxValue() const;

    void updateRange();
    void increaseRange(const unsigned int increment);
    void decreaseRange(const unsigned int decrement);

    sensor& setName(const QString newName);
    sensor& setDescription(const QString newDescription);

    virtual sensor& setMinValue(const double value) = 0;
    virtual sensor& setMaxValue(const double value) = 0;

    virtual void updateTable() = 0;
    virtual void updateResultTable(const QModelIndex &topLeft, const QModelIndex &bottomRight) = 0;
    virtual void accept(visitor* visitor) = 0;

signals:
    //segnali per modifiche
    void nameChanged(const QString &newName);
    void descriptionChanged(const QString newDescription);
    void minValueChanged(const double newMinValue);
    void maxValueChanged(const double newMaxValue);


};

}

#endif // SENSOR_H
