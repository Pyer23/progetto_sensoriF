#ifndef HUMIDITYSENSOREDITWIDGET_H
#define HUMIDITYSENSOREDITWIDGET_H

#include "../model/humiditysensor.h"
#include "basehumiditysensorwidget.h"

namespace sensor {

class HumiditySensorEditWidget : public BaseHumiditySensorWidget {
    Q_OBJECT
public:
    explicit HumiditySensorEditWidget(QWidget *parent = nullptr);

    void setHumiditySensor(humiditysensor *hum);

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);

private:
    humiditysensor *humiditySensorX;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;
    QDoubleSpinBox *maxValueSpinBox;

    QPushButton *changeButton;

    QFormLayout *formLayout;

    QDoubleSpinBox *volumeSpinBox;
};

}

#endif // HUMIDITYSENSOREDITWIDGET_H
