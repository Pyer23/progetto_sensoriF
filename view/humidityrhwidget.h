#ifndef HUMIDITYRHWIDGET_H
#define HUMIDITYRHWIDGET_H

#include "../model/humidityrhsensor.h"
#include "basehumiditysensorwidget.h"

namespace sensor {

class HumidityRHWidget : public BaseHumiditySensorWidget {
    Q_OBJECT
public:
    HumidityRHWidget(QWidget *parent = nullptr);
    void setHumiditySensor(humidityRHsensor *hum);
    void updateChart();

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void increaseRange();
    void decreaseRange();

    void saveChartImage();

private:
    humidityRHsensor *humiditySensorX;

    QToolBar *toolBar;
    QAction *increaseRangeAction;
    QAction *decreaseRangeAction;
    QAction *saveChartAction;

    QChart *chart;
    QSplineSeries *series;
    QChartView *chartView;
    QTableView* variableTable;
    QTableView* resultTable;

    QPushButton *moreRange;
    QPushButton *lessRange;

    QGridLayout* gridLayout;
};

}

#endif // HUMIDITYRHWIDGET_H
