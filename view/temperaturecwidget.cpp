#include "temperaturecwidget.h"
#include <QtCharts>

namespace sensor {

TemperatureCWidget::TemperatureCWidget(QWidget *parent) : BaseTemperatureSensorWidget(parent),
    temperatureSensorX(nullptr) {

    toolBar = new QToolBar(this);
    increaseRangeAction = new QAction(QIcon(QPixmap(":/images/more_range.ico")), tr("Aumenta il range"), this);
    decreaseRangeAction = new QAction(QIcon(QPixmap(":/images/less_range.ico")), tr("Diminuisci il range"), this);
    saveChartAction = new QAction(QIcon(QPixmap(":/images/save_chartimage.ico")), tr("Salva grafico come immagine"), this);
    toolBar->addAction(increaseRangeAction);
    toolBar->addAction(decreaseRangeAction);
    toolBar->addAction(saveChartAction);

    chart = new QChart();
    series = new QBarSeries(this);
    barSet = new QBarSet("Rilevazioni a contatto", this);
    chartView = new QChartView(chart);


    variableTable = new QTableView(this);
    resultTable = new QTableView(this);

    moreRange = new QPushButton("Aumenta il range", this);
    lessRange = new QPushButton("Diminuisci il range", this);
    moreRange->setStyleSheet("background-color: #008000; color: white");
    lessRange->setStyleSheet("background-color: #FF0000; color: white;");

    gridLayout = new QGridLayout(this);

    gridLayout->addWidget(toolBar, 0, 0, 1, 10);
    gridLayout->addWidget(nameLabel, 1, 0, 1, 1);
    gridLayout->addWidget(descriptionLabel, 2, 0, 1, 1);
    gridLayout->addWidget(new QLabel("Minima rilevazione:"), 3, 0, 1, 1);
    gridLayout->addWidget(minValueLabel, 3, 1, 1, 1);
    gridLayout->addWidget(new QLabel("Massima rilevazione:"), 3, 2, 1, 1);
    gridLayout->addWidget(maxValueLabel, 3, 3, 1, 1);
    gridLayout->addWidget(new QLabel("Resistenza:"), 4, 0, 1, 1);
    gridLayout->addWidget(resistanceLabel, 4, 1, 1, 1);
    gridLayout->addWidget(moreRange, 5, 0, 1, 2);
    gridLayout->addWidget(lessRange, 5, 2, 1, 2);
    gridLayout->addWidget(variableTable, 6, 0, 1, 4);
    gridLayout->addWidget(resultTable, 7, 0, 1, 4);
    gridLayout->addWidget(chartView, 0, 4, 9, 6);


    connect(increaseRangeAction, &QAction::triggered, this, &TemperatureCWidget::increaseRange);
    connect(decreaseRangeAction, &QAction::triggered, this, &TemperatureCWidget::decreaseRange);
    connect(saveChartAction, &QAction::triggered, this, &TemperatureCWidget::saveChartImage);
}

void TemperatureCWidget::setTemperatureSensor(temperatureCsensor* temp) {
    temperatureSensorX = temp;
    if (temperatureSensorX) {
        connect(temperatureSensorX->getResultTable(), &table::dataChanged, this, &TemperatureCWidget::updateChart);
        connect(temperatureSensorX->getResultTable(), &table::columnsInserted, this, &TemperatureCWidget::updateChart);
        connect(temperatureSensorX->getResultTable(), &table::columnsRemoved, this, &TemperatureCWidget::updateChart);

        connect(temperatureSensorX, &temperatureCsensor::nameChanged, this, &TemperatureCWidget::updateNameLabel);
        connect(temperatureSensorX, &temperatureCsensor::descriptionChanged, this, &TemperatureCWidget::updateDescriptionLabel);
        connect(temperatureSensorX, &temperatureCsensor::minValueChanged, this, &TemperatureCWidget::updateMinValueLabel);
        connect(temperatureSensorX, &temperatureCsensor::maxValueChanged, this, &TemperatureCWidget::updateMaxValueLabel);

        connect(temperatureSensorX, &temperatureCsensor::resistanceChanged, this, &TemperatureCWidget::updateResistanceLabel);

        connect(moreRange, &QPushButton::clicked, this, &TemperatureCWidget::increaseRange);
        connect(lessRange, &QPushButton::clicked, this, &TemperatureCWidget::decreaseRange);

    }
    updateWidget();
}

void TemperatureCWidget::updateWidget() {
    if (temperatureSensorX) {
        nameLabel->setText(temperatureSensorX->getName());
        descriptionLabel->setText(temperatureSensorX->getDescription());
        minValueLabel->setText(QString::number(temperatureSensorX->getMinValue()));
        maxValueLabel->setText(QString::number(temperatureSensorX->getMaxValue()));
        resistanceLabel->setText(QString::number(temperatureSensorX->getResistance()));

        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        if (temperatureSensorX->getVariableTable()) {
            variableTable->setModel(temperatureSensorX->getVariableTable());
            variableTable->verticalHeader()->setStretchLastSection(true);
        }
        if (temperatureSensorX->getResultTable()) {
            resultTable->setModel(temperatureSensorX->getResultTable());
            resultTable->verticalHeader()->setStretchLastSection(true);
        }

        series->clear();

        for (auto set : series->barSets()) {
            series->remove(set);
            delete set;
        }
        QBarSet *newBarSet = new QBarSet("Rilevazioni a contatto");
        for (int column = 0; column < temperatureSensorX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = temperatureSensorX->getResultTable()->index(0, column);
            double value = temperatureSensorX->getResultTable()->data(index).toDouble();
            newBarSet->append(value);
        }
        series->append(newBarSet);
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = temperatureSensorX->getMinValue() / temperatureSensorX->getResistance();
                double maxPoint = temperatureSensorX->getMaxValue() / temperatureSensorX->getResistance();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }
}

void TemperatureCWidget::updateChart() {

    if (temperatureSensorX) {
        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        series->clear();

        for (auto set : series->barSets()) {
            series->remove(set);
            delete set;
        }
        QBarSet *newBarSet = new QBarSet("Rilevazioni a contatto");
        for (int column = 0; column < temperatureSensorX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = temperatureSensorX->getResultTable()->index(0, column);
            double value = temperatureSensorX->getResultTable()->data(index).toDouble();
            newBarSet->append(value);
        }
        series->append(newBarSet);
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = temperatureSensorX->getMinValue() / temperatureSensorX->getResistance();
                double maxPoint = temperatureSensorX->getMaxValue() / temperatureSensorX->getResistance();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }

}

void TemperatureCWidget::updateSensor(){
    return;
}

void TemperatureCWidget::increaseRange(){
    if (temperatureSensorX) {
        temperatureSensorX->increaseRange(1);
    }
}

void TemperatureCWidget::decreaseRange(){
    if (temperatureSensorX) {
        temperatureSensorX->decreaseRange(1);
    }
}

void TemperatureCWidget::saveChartImage() {
    if (chartView) {
        QImage chartImage = chartView->grab().toImage();

        QString fileName = QFileDialog::getSaveFileName(this, tr("Salva grafico come immagine"), "", tr("Immagini (*.png)"));

        if (!fileName.isEmpty()) {
            if (chartImage.save(fileName)) {
                qDebug() << "Grafico salvato come immagine con successo!";
            } else {
                qDebug() << "Errore durante il salvataggio del grafico come immagine!";
            }
        }
    } else {
        qDebug() << "Impossibile salvare il grafico: chartView non valido!";
    }
}

}
