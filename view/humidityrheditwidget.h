#ifndef HUMIDITYRHEDITWIDGET_H
#define HUMIDITYRHEDITWIDGET_H

#include "../model/humidityrhsensor.h"
#include "basehumiditysensorwidget.h"

namespace sensor {

class HumidityRHEditWidget : public BaseHumiditySensorWidget {
    Q_OBJECT
public:
    explicit HumidityRHEditWidget(QWidget *parent = nullptr);

    void setHumiditySensor(humidityRHsensor *hum);

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);

private:
    humidityRHsensor *humiditySensorX;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;

    QPushButton *changeButton;

    QFormLayout *formLayout;

    QDoubleSpinBox *volumeSpinBox;
    QDoubleSpinBox *maxSaturationSpinBox;
};

}
#endif // HUMIDITYRHEDITWIDGET_H
