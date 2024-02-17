#include "humidityrhwidget.h"
#include <QtCharts>

namespace sensor {

HumidityRHWidget::HumidityRHWidget(QWidget *parent) : BaseHumiditySensorWidget(parent),
    humiditySensorX(nullptr) {

    toolBar = new QToolBar(this);
    increaseRangeAction = new QAction(QIcon(QPixmap(":/images/more_range.ico")), tr("Aumenta il range"), this);
    decreaseRangeAction = new QAction(QIcon(QPixmap(":/images/less_range.ico")), tr("Diminuisci il range"), this);
    saveChartAction = new QAction(QIcon(QPixmap(":/images/save_chartimage.ico")), tr("Salva grafico come immagine"), this);
    toolBar->addAction(increaseRangeAction);
    toolBar->addAction(decreaseRangeAction);
    toolBar->addAction(saveChartAction);

    chart = new QChart();
    series = new QSplineSeries(this);
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
    gridLayout->addWidget(new QLabel("Volume:"), 4, 0, 1, 1);
    gridLayout->addWidget(volumeLabel, 4, 1, 1, 1);
    gridLayout->addWidget(new QLabel("Massima saturazione:"), 5, 0, 1, 1);
    gridLayout->addWidget(maxSaturationLabel, 5, 1, 1, 1);
    gridLayout->addWidget(moreRange, 6, 0, 1, 2);
    gridLayout->addWidget(lessRange, 6, 2, 1, 2);
    gridLayout->addWidget(variableTable, 7, 0, 1, 4);
    gridLayout->addWidget(resultTable, 8, 0, 1, 4);
    gridLayout->addWidget(chartView, 0, 4, 10, 6);

    connect(increaseRangeAction, &QAction::triggered, this, &HumidityRHWidget::increaseRange);
    connect(decreaseRangeAction, &QAction::triggered, this, &HumidityRHWidget::decreaseRange);
    connect(saveChartAction, &QAction::triggered, this, &HumidityRHWidget::saveChartImage);
}

void HumidityRHWidget::setHumiditySensor(humidityRHsensor* hum) {
    humiditySensorX = hum;
    if (humiditySensorX) {
        connect(humiditySensorX->getResultTable(), &table::dataChanged, this, &HumidityRHWidget::updateChart);
        connect(humiditySensorX->getResultTable(), &table::columnsInserted, this, &HumidityRHWidget::updateChart);
        connect(humiditySensorX->getResultTable(), &table::columnsRemoved, this, &HumidityRHWidget::updateChart);

        connect(humiditySensorX, &humidityRHsensor::nameChanged, this, &HumidityRHWidget::updateNameLabel);
        connect(humiditySensorX, &humidityRHsensor::descriptionChanged, this, &HumidityRHWidget::updateDescriptionLabel);
        connect(humiditySensorX, &humidityRHsensor::minValueChanged, this, &HumidityRHWidget::updateMinValueLabel);

        connect(humiditySensorX, &humidityRHsensor::volumeChanged, this, &HumidityRHWidget::updateVolumeLabel);
        connect(humiditySensorX, &humidityRHsensor::maxValueChanged, this, &HumidityRHWidget::updateMaxSaturationLabel);

        connect(moreRange, &QPushButton::clicked, this, &HumidityRHWidget::increaseRange);
        connect(lessRange, &QPushButton::clicked, this, &HumidityRHWidget::decreaseRange);

    }
    updateWidget();
}

void HumidityRHWidget::updateWidget() {
    if (humiditySensorX) {
        nameLabel->setText(humiditySensorX->getName());
        descriptionLabel->setText(humiditySensorX->getDescription());
        minValueLabel->setText(QString::number(humiditySensorX->getMinValue()));
        volumeLabel->setText(QString::number(humiditySensorX->getVolume()));
        maxSaturationLabel->setText(QString::number(humiditySensorX->getMaxValue()));

        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        if (humiditySensorX->getVariableTable()) {
            variableTable->setModel(humiditySensorX->getVariableTable());
            variableTable->verticalHeader()->setStretchLastSection(true);
        }
        if (humiditySensorX->getResultTable()) {
            resultTable->setModel(humiditySensorX->getResultTable());
            resultTable->verticalHeader()->setStretchLastSection(true);
        }
        // Aggiorna il grafico
        series->clear();
        for (int column = 0; column < humiditySensorX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = humiditySensorX->getResultTable()->index(0, column);
            double value = humiditySensorX->getResultTable()->data(index).toDouble();
            series->append(column, value);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = (humiditySensorX->getMinValue() / humiditySensorX->getVolume()) / humiditySensorX->getMaxValue() * 100;
                double maxPoint = (humiditySensorX->getMaxValue() / humiditySensorX->getVolume()) / humiditySensorX->getMaxValue() * 100;
                double minV = 0;
                double maxV = maxPoint+(maxPoint);
                if(minPoint == 0){
                    minV = minPoint-(maxPoint);
                }
                if(minPoint < 0 && maxPoint < 0){
                    minV = minPoint+(maxPoint);  //minV negativo (-x)+(-y)= -z
                    maxV = maxPoint-(maxPoint);
                }
                if(minPoint < 0 && maxPoint > 0){ //minV negativo (-x)-(+y)= -z
                    minV = minPoint-(maxPoint);
                }
                if(minPoint > 0){
                    minV = minPoint-(maxPoint/2);
                }
                verticalAxis->setRange(minV, maxV);
                //minV e maxV scelti dopo test sulla visualizzazione dei vertici del grafico, non con formule relative a parabole o altre funzioni
            }
        }
    }
}

void HumidityRHWidget::updateChart() {

    if (humiditySensorX) {
        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        series->clear();

        for (int column = 0; column < humiditySensorX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = humiditySensorX->getResultTable()->index(0, column);
            double value = humiditySensorX->getResultTable()->data(index).toDouble();
            series->append(column, value);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = (humiditySensorX->getMinValue() / humiditySensorX->getVolume()) / humiditySensorX->getMaxValue() * 100;
                double maxPoint = (humiditySensorX->getMaxValue() / humiditySensorX->getVolume()) / humiditySensorX->getMaxValue() * 100;
                double minV = 0;
                double maxV = maxPoint+(maxPoint);
                if(minPoint == 0){
                    minV = minPoint-(maxPoint);
                }
                if(minPoint < 0 && maxPoint < 0){
                    minV = minPoint+(maxPoint);  //minV negativo (-x)+(-y)= -z
                    maxV = maxPoint-(maxPoint);
                }
                if(minPoint < 0 && maxPoint > 0){ //minV negativo (-x)-(+y)= -z
                    minV = minPoint-(maxPoint);
                }
                if(minPoint > 0){
                    minV = minPoint-(maxPoint/2);
                }
                verticalAxis->setRange(minV, maxV);
                //minV e maxV scelti dopo test sulla visualizzazione dei vertici del grafico, non con formule relative a parabole o altre funzioni
            }
        }
    }

}

void HumidityRHWidget::updateSensor(){
    return;
}

void HumidityRHWidget::increaseRange(){
    if (humiditySensorX) {
        humiditySensorX->increaseRange(1);
    }
}

void HumidityRHWidget::decreaseRange(){
    if (humiditySensorX) {
        humiditySensorX->decreaseRange(1);
    }
}

void HumidityRHWidget::saveChartImage() {
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
