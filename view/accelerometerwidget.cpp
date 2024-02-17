#include "accelerometerwidget.h"
#include <QtCharts>

namespace sensor {

AccelerometerWidget::AccelerometerWidget(QWidget *parent) : BaseAccelerometerWidget(parent),
    accelerometerX(nullptr) {

    toolBar = new QToolBar(this);
    increaseRangeAction = new QAction(QIcon(QPixmap(":/images/more_range.ico")), tr("Aumenta il range"), this);
    decreaseRangeAction = new QAction(QIcon(QPixmap(":/images/less_range.ico")), tr("Diminuisci il range"), this);
    saveChartAction = new QAction(QIcon(QPixmap(":/images/save_chartimage.ico")), tr("Salva grafico come immagine"), this);
    toolBar->addAction(increaseRangeAction);
    toolBar->addAction(decreaseRangeAction);
    toolBar->addAction(saveChartAction);

    chart = new QChart();
    series = new QLineSeries(this);
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
    gridLayout->addWidget(new QLabel("Minima rilevazione:", this), 3, 0, 1, 1);
    gridLayout->addWidget(minValueLabel, 3, 1, 1, 1);
    gridLayout->addWidget(new QLabel("Massima rilevazione:", this), 3, 2, 1, 1);
    gridLayout->addWidget(maxValueLabel, 3, 3, 1, 1);
    gridLayout->addWidget(new QLabel("Massa:", this), 4, 0, 1, 1);
    gridLayout->addWidget(massLabel, 4, 1, 1, 1);
    gridLayout->addWidget(moreRange, 5, 0, 1, 2);
    gridLayout->addWidget(lessRange, 5, 2, 1, 2);
    gridLayout->addWidget(variableTable, 6, 0, 1, 4);
    gridLayout->addWidget(resultTable, 7, 0, 1, 4);
    gridLayout->addWidget(chartView, 0, 4, 9, 6);

    connect(increaseRangeAction, &QAction::triggered, this, &AccelerometerWidget::increaseRange);
    connect(decreaseRangeAction, &QAction::triggered, this, &AccelerometerWidget::decreaseRange);
    connect(saveChartAction, &QAction::triggered, this, &AccelerometerWidget::saveChartImage);

}

void AccelerometerWidget::setAccelerometer(accelerometer* acc) {
    accelerometerX = acc;
    if (accelerometerX) {

        connect(accelerometerX->getResultTable(), &table::dataChanged, this, &AccelerometerWidget::updateChart);
        connect(accelerometerX->getResultTable(), &table::columnsInserted, this, &AccelerometerWidget::updateChart);
        connect(accelerometerX->getResultTable(), &table::columnsRemoved, this, &AccelerometerWidget::updateChart);

        connect(accelerometerX, &accelerometer::nameChanged, this, &AccelerometerWidget::updateNameLabel);
        connect(accelerometerX, &accelerometer::descriptionChanged, this, &AccelerometerWidget::updateDescriptionLabel);
        connect(accelerometerX, &accelerometer::minValueChanged, this, &AccelerometerWidget::updateMinValueLabel);
        connect(accelerometerX, &accelerometer::maxValueChanged, this, &AccelerometerWidget::updateMaxValueLabel);

        connect(accelerometerX, &accelerometer::massChanged, this, &AccelerometerWidget::updateMassLabel);

        connect(moreRange, &QPushButton::clicked, this, &AccelerometerWidget::increaseRange);
        connect(lessRange, &QPushButton::clicked, this, &AccelerometerWidget::decreaseRange);

    }
    updateWidget();
}

void AccelerometerWidget::updateWidget() {
    if (accelerometerX) {
        nameLabel->setText(accelerometerX->getName());
        descriptionLabel->setText(accelerometerX->getDescription());
        minValueLabel->setText(QString::number(accelerometerX->getMinValue()));
        maxValueLabel->setText(QString::number(accelerometerX->getMaxValue()));
        massLabel->setText(QString::number(accelerometerX->getMass()));

        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        if (accelerometerX->getVariableTable()) {
            variableTable->setModel(accelerometerX->getVariableTable());
            variableTable->verticalHeader()->setStretchLastSection(true);
        }
        if (accelerometerX->getResultTable()) {
            resultTable->setModel(accelerometerX->getResultTable());
            resultTable->verticalHeader()->setStretchLastSection(true);
        }
        series->clear();
        for (int column = 0; column < accelerometerX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = accelerometerX->getResultTable()->index(0, column);
            double value = accelerometerX->getResultTable()->data(index).toDouble();
            series->append(column, value);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = accelerometerX->getMinValue() * accelerometerX->getMass();
                double maxPoint = accelerometerX->getMaxValue() * accelerometerX->getMass();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }
}

void AccelerometerWidget::updateChart() {

    if (accelerometerX) {
        if (!chart->series().isEmpty()) {
            chart->removeSeries(series);
        }

        series->clear();

        for (int column = 0; column < accelerometerX->getResultTable()->columnCount(); ++column) {
            QModelIndex index = accelerometerX->getResultTable()->index(0, column);
            double value = accelerometerX->getResultTable()->data(index).toDouble();
            series->append(column, value);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();

        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            QValueAxis *verticalAxis = qobject_cast<QValueAxis *>(verticalAxes.first());
            if (verticalAxis) {
                double minPoint = accelerometerX->getMinValue() * accelerometerX->getMass();
                double maxPoint = accelerometerX->getMaxValue() * accelerometerX->getMass();
                verticalAxis->setRange(minPoint, maxPoint);
            }
        }
    }

}

void AccelerometerWidget::updateSensor(){
    return;
}

void AccelerometerWidget::increaseRange(){
    if (accelerometerX) {
        accelerometerX->increaseRange(1);
    }
}

void AccelerometerWidget::decreaseRange(){
    if (accelerometerX) {
        accelerometerX->decreaseRange(1);
    }
}

void AccelerometerWidget::saveChartImage() {
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
