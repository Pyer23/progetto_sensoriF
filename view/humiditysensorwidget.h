#ifndef HUMIDITYSENSORWIDGET_H
#define HUMIDITYSENSORWIDGET_H

#include "../model/humiditysensor.h"
#include "basehumiditysensorwidget.h"

namespace sensor {

class HumiditySensorWidget : public BaseHumiditySensorWidget {
    Q_OBJECT
public:
    HumiditySensorWidget(QWidget *parent = nullptr);
    void setHumiditySensor(humiditysensor *hum);
    void updateChart();

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void increaseRange();
    void decreaseRange();

    void saveChartImage();

private:
    humiditysensor *humiditySensorX;

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

#endif // HUMIDITYSENSORWIDGET_H
