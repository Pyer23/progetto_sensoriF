#include "basehumiditysensorwidget.h"

namespace sensor {

BaseHumiditySensorWidget::BaseHumiditySensorWidget(QWidget *parent)
    : BaseSensorWidget(parent)
{
    volumeLabel = new QLabel(this);
    maxSaturationLabel = new QLabel(this);
}

void BaseHumiditySensorWidget::updateVolumeLabel(const double &volume) {
    volumeLabel->setText(QString::number(volume));
}

void BaseHumiditySensorWidget::updateMaxSaturationLabel(const double &maxSaturation) {
    maxSaturationLabel->setText(QString::number(maxSaturation));
}

}
