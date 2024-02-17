#ifndef ACCELEROMETERWIDGET_H
#define ACCELEROMETERWIDGET_H

#include "../model/accelerometer.h"
#include "baseaccelerometerwidget.h"

namespace sensor {

class AccelerometerWidget : public BaseAccelerometerWidget {
    Q_OBJECT
public:
    AccelerometerWidget(QWidget *parent = nullptr);
    void setAccelerometer(accelerometer *acc);
    void updateChart();

private slots:
    void updateWidget() override;
    void updateSensor() override;

    void increaseRange();
    void decreaseRange();

    void saveChartImage();

private:
    accelerometer *accelerometerX;

    QToolBar *toolBar;
    QAction *increaseRangeAction;
    QAction *decreaseRangeAction;
    QAction *saveChartAction;

    QChart *chart;
    QChartView *chartView;
    QTableView* variableTable;
    QTableView* resultTable;
    QLineSeries *series;

    QPushButton *moreRange;
    QPushButton *lessRange;

    QGridLayout *gridLayout;
};

} // namespace sensor

#endif // ACCELEROMETERWIDGET_H
