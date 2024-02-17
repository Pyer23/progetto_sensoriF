#ifndef ACCELEROMETEREDITWIDGET_H
#define ACCELEROMETEREDITWIDGET_H

#include "../model/accelerometer.h"
#include "baseaccelerometerwidget.h"

namespace sensor {

class AccelerometerEditWidget : public BaseAccelerometerWidget {
    Q_OBJECT
public:
    explicit AccelerometerEditWidget(QWidget *parent = nullptr);
    void setAccelerometer(accelerometer *acc);

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);

private:
    accelerometer *accelerometerX;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;
    QDoubleSpinBox *maxValueSpinBox;

    QPushButton *changeButton;

    QFormLayout *formLayout;

    QDoubleSpinBox *massSpinBox;
};

}

#endif // ACCELEROMETEREDITWIDGET_H
