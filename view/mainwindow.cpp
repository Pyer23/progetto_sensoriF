#include "mainwindow.h"

#include "../model/accelerometer.h"

#include "../model/humiditysensor.h"
#include "../model/humidityrhsensor.h"

#include "../model/temperaturesensor.h"
#include "../model/temperaturecsensor.h"

#include "../model/sensorcontainer.h"

#include "sensorsearchwidget.h"

#include <QtWidgets>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sensor::accelerometer* a1 = new sensor::accelerometer("ACCX23", "Accelerometro x23 per oggetti vari", 10, 0, 50, 15);
    sensor::accelerometer* a2 = new sensor::accelerometer("ACCK18", "Accelerometro k24 per simulazioni varie", 9, -12, -1, 12);
    sensor::accelerometer* a3 = new sensor::accelerometer("ACCELEROMETRO R27", "Accelerometro per test", 19, 1, 10, 10);
    sensor::accelerometer* a4 = new sensor::accelerometer("A99", "Simulatore di accelerometro", 5, 5, 100, 99);
    sensor::accelerometer* a5 = new sensor::accelerometer("ACC21", "accelerometro 2", 5, -3, 10, 1);


    sensor::humiditysensor* h1 = new sensor::humiditysensor("HUMah19", "Rileva umidità assoluta", 18, -5, 12, 50);
    sensor::humiditysensor* h2 = new sensor::humiditysensor("HumAH99", "Sensore di umidità assoluta basico", 23, 1, 10, 18);
    sensor::humiditysensor* h3 = new sensor::humiditysensor("H25", "Simulatore di sensore di umidità", 50, 5, 80, 19);
    sensor::humiditysensor* h4 = new sensor::humiditysensor("HumidityX24", "Sensore che simula la variazione dell'umidità nell'ambiente", 25, 2, 51, 40);

    sensor::humidityRHsensor* rh1 = new sensor::humidityRHsensor("HRH", "Sensore di umidità relativa", 3, 10, 20, 20);
    sensor::humidityRHsensor* rh2 = new sensor::humidityRHsensor("hrh25", "Sensore di umidità relativa indoor", 27, -4, 10, 30);
    sensor::humidityRHsensor* rh3 = new sensor::humidityRHsensor("RHW77", "Sensore di umidità che calcola l'umidità relativa", 8, 0, 15, 45);
    sensor::humidityRHsensor* rh4 = new sensor::humidityRHsensor("HUMRH", "sensore HUMRH", 12, 1, 12, 10);

    sensor::temperaturesensor* t1 = new sensor::temperaturesensor("TEMP18", "sensore di temperatura", 23, 1, 54);
    sensor::temperaturesensor* t2 = new sensor::temperaturesensor("TEMPX99", "sensore che rileva la temperatura", 32, -34, 20);
    sensor::temperaturesensor* t3 = new sensor::temperaturesensor("temperatureS", "sensore che mostra variazioni rilevate", 43, -50, 30);
    sensor::temperaturesensor* t4 = new sensor::temperaturesensor("temp23", "sensore23 temp senza contatto", 2, -9, 33);

    sensor::temperatureCsensor* tc1 = new sensor::temperatureCsensor("tempC", "sensore di temperatura per metalli", 4, -4, 50, 1);
    sensor::temperatureCsensor* tc2 = new sensor::temperatureCsensor("TC19", "sensore di temperatura a contatto", 7, -9, 50, 15);
    sensor::temperatureCsensor* tc3 = new sensor::temperatureCsensor("TCM22", "temperatura ridotta dalla reistenza", 30, 9, 50, 18);
    sensor::temperatureCsensor* tc4 = new sensor::temperatureCsensor("TemperatureSensorContact", "temperatura a contatto variabile in base alla reistenza", 10, 0, 50, 23);

    sensor::SensorContainer *container = new sensor::SensorContainer();
    container->addSensor(a1);
    container->addSensor(a2);
    container->addSensor(a3);
    container->addSensor(a4);
    container->addSensor(a5);

    container->addSensor(h1);
    container->addSensor(h2);
    container->addSensor(h3);
    container->addSensor(h4);

    container->addSensor(rh1);
    container->addSensor(rh2);
    container->addSensor(rh3);
    container->addSensor(rh4);
    container->addSensor(t1);
    container->addSensor(t2);
    container->addSensor(t3);
    container->addSensor(t4);
    container->addSensor(tc1);
    container->addSensor(tc2);
    container->addSensor(tc3);
    container->addSensor(tc4);

    QWidget *window = new QWidget();
    QStackedWidget *stacked = new QStackedWidget;

    QVBoxLayout *layout = new QVBoxLayout(window);
    QPushButton *homePage = new QPushButton("Pagina iniziale");

    sensor::SensorSearchWidget *search = new sensor::SensorSearchWidget(this);
    search->setSensorContainer(*container);

    layout->addWidget(search);

    setCentralWidget(window);
    setWindowTitle("sensOne");
    setWindowIcon(QIcon("../images/sensone_icon.ico"));

    connect(homePage, &QPushButton::clicked, this, [=]() {
        stacked->setCurrentWidget(search);
    });

}

MainWindow::~MainWindow()
{
}

