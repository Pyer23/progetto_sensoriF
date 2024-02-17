#ifndef TEMPERATURECEDITWIDGET_H
#define TEMPERATURECEDITWIDGET_H

#include "../model/temperaturecsensor.h"
#include "basetemperaturesensorwidget.h"

namespace sensor {

class TemperatureCEditWidget : public BaseTemperatureSensorWidget {
    Q_OBJECT
public:
    explicit TemperatureCEditWidget(QWidget *parent = nullptr);

    void setTemperatureSensor(temperatureCsensor *temp);

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);

private:
    temperatureCsensor *temperatureSensorX;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;
    QDoubleSpinBox *maxValueSpinBox;

    QPushButton *changeButton;

    QFormLayout *formLayout;

    QDoubleSpinBox *resistanceSpinBox;
};

}

#endif // TEMPERATURECEDITWIDGET_H
