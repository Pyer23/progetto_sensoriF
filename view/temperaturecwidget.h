#ifndef TEMPERATURECWIDGET_H
#define TEMPERATURECWIDGET_H

#include "../model/temperaturecsensor.h"
#include "basetemperaturesensorwidget.h"

namespace sensor {

class TemperatureCWidget: public BaseTemperatureSensorWidget {
    Q_OBJECT
public:
    TemperatureCWidget(QWidget *parent = nullptr);
    void setTemperatureSensor(temperatureCsensor *temp);
    void updateChart();

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void increaseRange();
    void decreaseRange();

    void saveChartImage();

private:
    temperatureCsensor *temperatureSensorX;

    QToolBar *toolBar;
    QAction *increaseRangeAction;
    QAction *decreaseRangeAction;
    QAction *saveChartAction;

    QChart *chart;
    QChartView *chartView;
    QTableView* variableTable;
    QTableView* resultTable;
    QBarSeries *series;
    QBarSet *barSet;

    QPushButton *moreRange;
    QPushButton *lessRange;

    QGridLayout *gridLayout;
};

}

#endif // TEMPERATURECWIDGET_H
