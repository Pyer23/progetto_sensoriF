#ifndef BASESENSORWIDGET_H
#define BASESENSORWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QTableView>
#include <QChart>
#include <QLineSeries>
#include <QSplineSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
#include <QToolBar>

namespace sensor {

class BaseSensorWidget : public QWidget {
    Q_OBJECT
public:
    explicit BaseSensorWidget(QWidget *parent = nullptr);

private slots:
    virtual void updateWidget() = 0;
    virtual void updateSensor() = 0;

protected:
    QLabel *nameLabel;
    QLabel *descriptionLabel;
    QLabel *minValueLabel;
    QLabel *maxValueLabel;

    void updateNameLabel(const QString &name);
    void updateDescriptionLabel(const QString &description);
    void updateMinValueLabel(const double &minValue);
    void updateMaxValueLabel(const double &maxValue);
};

}

#endif // BASESENSORWIDGET_H
