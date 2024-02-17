#ifndef BASEHUMIDITYSENSORWIDGET_H
#define BASEHUMIDITYSENSORWIDGET_H

#include "basesensorwidget.h"

namespace sensor {

class BaseHumiditySensorWidget : public BaseSensorWidget
{
    Q_OBJECT
public:
    explicit BaseHumiditySensorWidget(QWidget *parent = nullptr);

protected:
    QLabel *volumeLabel;
    QLabel *maxSaturationLabel;

    void updateVolumeLabel(const double &volume);
    void updateMaxSaturationLabel(const double &maxSaturation);
};

}
#endif // BASEHUMIDITYSENSORWIDGET_H
