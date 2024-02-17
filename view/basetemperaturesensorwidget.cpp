#include "basetemperaturesensorwidget.h"

namespace sensor {

BaseTemperatureSensorWidget::BaseTemperatureSensorWidget(QWidget *parent)
    : BaseSensorWidget(parent)
{
    resistanceLabel = new QLabel(this);
}

void BaseTemperatureSensorWidget::updateResistanceLabel(const double &resistance) {
    resistanceLabel->setText(QString::number(resistance));
}

}
