#ifndef TEMPERATURESENSOREDITWIDGET_H
#define TEMPERATURESENSOREDITWIDGET_H

#include "../model/temperaturesensor.h"
#include "basesensorwidget.h"

namespace sensor {

class TemperatureSensorEditWidget : public BaseSensorWidget {
    Q_OBJECT
public:
    explicit TemperatureSensorEditWidget(QWidget *parent = nullptr);

    void setTemperatureSensor(temperaturesensor *temp);

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);

private:
    temperaturesensor *temperatureSensorX;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;
    QDoubleSpinBox *maxValueSpinBox;

    QPushButton *changeButton;

    QFormLayout *formLayout;
};

}

#endif // TEMPERATURESENSOREDITWIDGET_H
