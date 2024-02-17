#include "chartvisitor.h"

namespace sensor {

void chartvisitor::visit(accelerometer* accelerometer) {
    AccelerometerWidget* chartWidget = new AccelerometerWidget();
    AccelerometerEditWidget* editWidget = new AccelerometerEditWidget();

    chartWidget->setAccelerometer(accelerometer);
    editWidget->setAccelerometer(accelerometer);

    QWidget* widget0 = new QWidget();
    QWidget* widget1 = new QWidget();
    stackedWidget = new QStackedWidget();

    QGridLayout* chartLayout = new QGridLayout(widget0);
    QGridLayout* editLayout = new QGridLayout(widget1);

    QPushButton* chartButton = new QPushButton("Torna al sensore");
    QPushButton* editButton = new QPushButton("Modifica sensore");

    editLayout->addWidget(editWidget, 0, 0, 9, 1);
    editLayout->addWidget(chartButton, 10, 0, 1, 1);

    chartLayout->addWidget(chartWidget, 0, 0, 9, 1);
    chartLayout->addWidget(editButton, 10, 0, 1, 1);

    stackedWidget->addWidget(widget0);
    stackedWidget->addWidget(widget1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget);

    connect(chartButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
    connect(editButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
}

void chartvisitor::visit(humiditysensor* humiditysensor){
    HumiditySensorWidget* chartWidget = new HumiditySensorWidget();
    HumiditySensorEditWidget* editWidget = new HumiditySensorEditWidget();

    chartWidget->setHumiditySensor(humiditysensor);
    editWidget->setHumiditySensor(humiditysensor);

    QWidget* widget0 = new QWidget();
    QWidget* widget1 = new QWidget();
    stackedWidget = new QStackedWidget();

    QGridLayout* chartLayout = new QGridLayout(widget0);
    QGridLayout* editLayout = new QGridLayout(widget1);

    QPushButton* chartButton = new QPushButton("Torna al sensore");
    QPushButton* editButton = new QPushButton("Modifica sensore");

    editLayout->addWidget(editWidget, 0, 0, 9, 1);
    editLayout->addWidget(chartButton, 10, 0, 1, 1);

    chartLayout->addWidget(chartWidget, 0, 0, 9, 1);
    chartLayout->addWidget(editButton, 10, 0, 1, 1);

    stackedWidget->addWidget(widget0);
    stackedWidget->addWidget(widget1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget);

    connect(chartButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
    connect(editButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
}

void chartvisitor::visit(humidityRHsensor* humidityRHsensor){
    HumidityRHWidget* chartWidget = new HumidityRHWidget();
    HumidityRHEditWidget* editWidget = new HumidityRHEditWidget();

    chartWidget->setHumiditySensor(humidityRHsensor);
    editWidget->setHumiditySensor(humidityRHsensor);

    QWidget* widget0 = new QWidget();
    QWidget* widget1 = new QWidget();
    stackedWidget = new QStackedWidget();

    QGridLayout* chartLayout = new QGridLayout(widget0);
    QGridLayout* editLayout = new QGridLayout(widget1);

    QPushButton* chartButton = new QPushButton("Torna al sensore");
    QPushButton* editButton = new QPushButton("Modifica sensore");

    editLayout->addWidget(editWidget, 0, 0, 9, 1);
    editLayout->addWidget(chartButton, 10, 0, 1, 1);

    chartLayout->addWidget(chartWidget, 0, 0, 9, 1);
    chartLayout->addWidget(editButton, 10, 0, 1, 1);

    stackedWidget->addWidget(widget0);
    stackedWidget->addWidget(widget1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget);

    connect(chartButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
    connect(editButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
}

void chartvisitor::visit(temperaturesensor* temperaturesensor){
    TemperatureSensorWidget* chartWidget = new TemperatureSensorWidget();
    TemperatureSensorEditWidget* editWidget = new TemperatureSensorEditWidget();

    chartWidget->setTemperatureSensor(temperaturesensor);
    editWidget->setTemperatureSensor(temperaturesensor);

    QWidget* widget0 = new QWidget();
    QWidget* widget1 = new QWidget();
    stackedWidget = new QStackedWidget();

    QGridLayout* chartLayout = new QGridLayout(widget0);
    QGridLayout* editLayout = new QGridLayout(widget1);

    QPushButton* chartButton = new QPushButton("Torna al sensore");
    QPushButton* editButton = new QPushButton("Modifica sensore");

    editLayout->addWidget(editWidget, 0, 0, 9, 1);
    editLayout->addWidget(chartButton, 10, 0, 1, 1);

    chartLayout->addWidget(chartWidget, 0, 0, 9, 1);
    chartLayout->addWidget(editButton, 10, 0, 1, 1);

    stackedWidget->addWidget(widget0);
    stackedWidget->addWidget(widget1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget);

    connect(chartButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
    connect(editButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
}

void chartvisitor::visit(temperatureCsensor* temperatureCsensor){
    TemperatureCWidget* chartWidget = new TemperatureCWidget();
    TemperatureCEditWidget* editWidget = new TemperatureCEditWidget();

    chartWidget->setTemperatureSensor(temperatureCsensor);
    editWidget->setTemperatureSensor(temperatureCsensor);

    QWidget* widget0 = new QWidget();
    QWidget* widget1 = new QWidget();
    stackedWidget = new QStackedWidget();

    QGridLayout* chartLayout = new QGridLayout(widget0);
    QGridLayout* editLayout = new QGridLayout(widget1);

    QPushButton* chartButton = new QPushButton("Torna al sensore");
    QPushButton* editButton = new QPushButton("Modifica sensore");

    editLayout->addWidget(editWidget, 0, 0, 9, 1);
    editLayout->addWidget(chartButton, 10, 0, 1, 1);

    chartLayout->addWidget(chartWidget, 0, 0, 9, 1);
    chartLayout->addWidget(editButton, 10, 0, 1, 1);

    stackedWidget->addWidget(widget0);
    stackedWidget->addWidget(widget1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget);

    connect(chartButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
    connect(editButton, &QPushButton::clicked, this, &chartvisitor::switchWidget);
}

QStackedWidget* chartvisitor::getWidget() const{
    return stackedWidget;
}

void chartvisitor::switchWidget() {
    int currentIndex = stackedWidget->currentIndex();
    int nextIndex = (currentIndex == 0) ? 1 : 0;
    stackedWidget->setCurrentIndex(nextIndex);
}

}
