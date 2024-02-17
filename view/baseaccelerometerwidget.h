#ifndef BASEACCELEROMETERWIDGET_H
#define BASEACCELEROMETERWIDGET_H

#include "basesensorwidget.h"

namespace sensor {

class BaseAccelerometerWidget : public BaseSensorWidget {
    Q_OBJECT
public:
    explicit BaseAccelerometerWidget(QWidget *parent = nullptr);

protected:
    QLabel *massLabel;

    void updateMassLabel(const double &mass);
};

}

#endif // BASEACCELEROMETERWIDGET_H
