#include "baseaccelerometerwidget.h"

namespace sensor {

BaseAccelerometerWidget::BaseAccelerometerWidget(QWidget *parent) : BaseSensorWidget(parent) {
    massLabel = new QLabel(this);
}

void BaseAccelerometerWidget::updateMassLabel(const double &mass) {
    massLabel->setText(QString::number(mass));
}

}
