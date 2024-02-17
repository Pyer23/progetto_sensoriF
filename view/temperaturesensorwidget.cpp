#include "temperaturesensorwidget.h"
#include <QtCharts>

namespace sensor {

TemperatureSensorWidget::TemperatureSensorWidget(QWidget *parent) : BaseSensorWidget(parent),
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
    barSet = new QBarSet("Rilevazioni", this);
    chartView = new QChartView(chart);

    variableTable = new QTableView(this);

    moreRange = new QPushButton("Aumenta il range", this);
    lessRange = new QPushButton("Diminuisci il range", this);
    moreRange->setStyleSheet("background-color: #008000; color: white");
    lessRange->setStyleSheet("background-color: #FF0000; color: white;");

    gridLayout = new QGridLayout(this);

    gridLayout->addWidget(toolBar, 0, 0, 1, 10);
    gridLayout->addWidget(nameLabel, 1, 0, 1, 1);
    gridLayout->addWidget(descriptionLabel, 2, 0, 1, 1);
    gridLayout->addWidget(new QLabel("Minima rilevazione:", this), 3, 0, 1, 1);
    gridLayout->addWidget(minValueLabel, 3, 1, 1, 1);
    gridLayout->addWidget(new QLabel("Massima rilevazione:", this), 3, 2, 1, 1);
    gridLayout->addWidget(maxValueLabel, 3, 3, 1, 1);
    gridLayout->addWidget(moreRange, 4, 0, 1, 2);
    gridLayout->addWidget(lessRange, 4, 2, 1, 2);
    gridLayout->addWidget(variableTable, 5, 0, 1, 4);
    gridLayout->addWidget(chartView, 0, 4, 6, 6);

    connect(increaseRangeAction, &QAction::triggered, this, &TemperatureSensorWidget::increaseRange);
    connect(decreaseRangeAction, &QAction::triggered, this, &TemperatureSensorWidget::decreaseRange);
    connect(saveChartAction, &QAction::triggered, this, &TemperatureSensorWidget::saveChartImage);
}

void TemperatureSensorWidget::setTemperatureSensor(temperaturesensor* temp) {
    temperatureSensorX = temp;
    if (temperatureSensorX) {
        connect(temperatureSensorX->getVariableTable(), &table::dataChanged, this, &TemperatureSensorWidget::updateChart);
        connect(temperatureSensorX->getVariableTable(), &table::columnsInserted, this, &TemperatureSensorWidget::updateChart);
        connect(temperatureSensorX->getVariableTable(), &table::columnsRemoved, this, &TemperatureSensorWidget::updateChart);

        connect(temperatureSensorX, &temperaturesensor::nameChanged, this, &TemperatureSensorWidget::updateNameLabel);
        connect(temperatureSensorX, &temperaturesensor::descriptionChanged, this, &TemperatureSensorWidget::updateDescriptionLabel);
        connect(temperatureSensorX, &temperaturesensor::minValueChanged, this, &TemperatureSensorWidget::updateMinValueLabel);
        connect(temperatureSensorX, &temperaturesensor::maxValueChanged, this, &TemperatureSensorWidget::updateMaxValueLabel);

        connect(moreRange, &QPushButton::clicked, this, &TemperatureSensorWidget::increaseRange);
        connect(lessRange, &QPushButton::clicked, this, &TemperatureSensorWidget::decreaseRange);

    }
    updateWidget();
}

void TemperatureSensorWidget::updateWidget() {
    if (temperatureSensorX) {
        nameLabel->setText(temperatureSensorX->getName());
        descriptionLabel->setText(temperatureSensorX->getDescription());
        minValueLabel->setText(QString::number(temperatureSensorX->getMinValue()));
        maxValueLabel->setText(QString::number(temperatureSensorX->getMaxValue()));

        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        if (temperatureSensorX->getVariableTable()) {
            variableTable->setModel(temperatureSensorX->getVariableTable());
            variableTable->verticalHeader()->setStretchLastSection(true);
        }
        if (temperatureSensorX->getResultTable()) {
            variableTable->setModel(temperatureSensorX->getVariableTable());
            variableTable->verticalHeader()->setStretchLastSection(true);
        }

        series->clear();
        for (auto set : series->barSets()) {
            series->remove(set);
            delete set;
        }
        QBarSet *newBarSet = new QBarSet("Rilevazioni");
        for (int column = 0; column < temperatureSensorX->getVariableTable()->columnCount(); ++column) {
            QModelIndex index = temperatureSensorX->getVariableTable()->index(0, column);
            double value = temperatureSensorX->getVariableTable()->data(index).toDouble();
            newBarSet->append(value);
        }
        series->append(newBarSet);
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = temperatureSensorX->getMinValue();
                double maxPoint = temperatureSensorX->getMaxValue();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }
}

void TemperatureSensorWidget::updateChart() {

    if (temperatureSensorX) {
        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        series->clear();

        for (auto set : series->barSets()) {
            series->remove(set);
            delete set;
        }
        QBarSet *newBarSet = new QBarSet("Rilevazioni");
        for (int column = 0; column < temperatureSensorX->getVariableTable()->columnCount(); ++column) {
            QModelIndex index = temperatureSensorX->getVariableTable()->index(0, column);
            double value = temperatureSensorX->getVariableTable()->data(index).toDouble();
            newBarSet->append(value);
        }
        series->append(newBarSet);
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = temperatureSensorX->getMinValue();
                double maxPoint = temperatureSensorX->getMaxValue();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }

}

void TemperatureSensorWidget::updateSensor(){
    return;
}

void TemperatureSensorWidget::increaseRange(){
    if (temperatureSensorX) {
        temperatureSensorX->increaseRange(1);
    }
}

void TemperatureSensorWidget::decreaseRange(){
    if (temperatureSensorX) {
        temperatureSensorX->decreaseRange(1);
    }
}

void TemperatureSensorWidget::saveChartImage() {
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
