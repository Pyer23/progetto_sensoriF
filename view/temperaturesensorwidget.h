#ifndef TEMPERATURESENSORWIDGET_H
#define TEMPERATURESENSORWIDGET_H

#include "../model/temperaturesensor.h"
#include "basesensorwidget.h"

namespace sensor {

class TemperatureSensorWidget : public BaseSensorWidget {
    Q_OBJECT
public:
    TemperatureSensorWidget(QWidget *parent = nullptr);
    void setTemperatureSensor(temperaturesensor *temp);
    void updateChart();

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void increaseRange();
    void decreaseRange();

    void saveChartImage();

private:
    temperaturesensor *temperatureSensorX;

    QToolBar *toolBar;
    QAction *increaseRangeAction;
    QAction *decreaseRangeAction;
    QAction *saveChartAction;

    QChart *chart;
    QChartView *chartView;
    QTableView* variableTable;
    QBarSeries *series;
    QBarSet *barSet;

    QPushButton *moreRange;
    QPushButton *lessRange;

    QGridLayout *gridLayout;
};

} // namespace sensor

#endif // TEMPERATURESENSORWIDGET_H
