#include "temperatureceditwidget.h"

namespace sensor {

TemperatureCEditWidget::TemperatureCEditWidget(QWidget *parent) : BaseTemperatureSensorWidget(parent),
    temperatureSensorX(nullptr) {

    nameLineEdit = new QLineEdit(this);
    descriptionLineEdit = new QLineEdit(this);

    minValueSpinBox = new QDoubleSpinBox(this);
    minValueSpinBox->setMinimum(-1000.0);
    minValueSpinBox->setMaximum(999.0);
    maxValueSpinBox = new QDoubleSpinBox(this);
    maxValueSpinBox->setMinimum(-999.0);
    maxValueSpinBox->setMaximum(1000.0);

    changeButton = new QPushButton("Cambia i parametri modificati", this);

    formLayout = new QFormLayout(this);

    resistanceSpinBox = new QDoubleSpinBox(this);
    resistanceSpinBox->setMinimum(0.0);
    resistanceSpinBox->setMaximum(1000.0);

    formLayout->addWidget(new QLabel("Nome:", this));
    formLayout->addWidget(nameLabel);
    formLayout->addWidget(nameLineEdit);
    formLayout->addWidget(new QLabel("Descrizione:", this));
    formLayout->addWidget(descriptionLabel);
    formLayout->addWidget(descriptionLineEdit);
    formLayout->addWidget(new QLabel("Minima Rilevazione:", this));
    formLayout->addWidget(minValueLabel);
    formLayout->addWidget(minValueSpinBox);
    formLayout->addWidget(new QLabel("Massima Rilevazione:", this));
    formLayout->addWidget(maxValueLabel);
    formLayout->addWidget(maxValueSpinBox);
    formLayout->addWidget(new QLabel("Resistenza:", this));
    formLayout->addWidget(resistanceLabel);
    formLayout->addWidget(resistanceSpinBox);
    formLayout->addWidget(changeButton);

    connect(changeButton, &QPushButton::clicked, this, &TemperatureCEditWidget::updateSensor);
}

void TemperatureCEditWidget::setTemperatureSensor(temperatureCsensor *temp) {
    temperatureSensorX = temp;
    if (temperatureSensorX) {
        nameLabel->setText(temperatureSensorX->getName());
        descriptionLabel->setText(temperatureSensorX->getDescription());
        minValueLabel->setText(QString::number(temperatureSensorX->getMinValue()));
        maxValueLabel->setText(QString::number(temperatureSensorX->getMaxValue()));
        resistanceLabel->setText(QString::number(temperatureSensorX->getResistance()));

        nameLineEdit->setText(temperatureSensorX->getName());
        descriptionLineEdit->setText(temperatureSensorX->getDescription());
        minValueSpinBox->setValue(temperatureSensorX->getMinValue());
        maxValueSpinBox->setValue(temperatureSensorX->getMaxValue());
        resistanceSpinBox->setValue(temperatureSensorX->getResistance());

        connect(temperatureSensorX, &temperatureCsensor::nameChanged, this, &TemperatureCEditWidget::updateNameLabel);
        connect(temperatureSensorX, &temperatureCsensor::descriptionChanged, this, &TemperatureCEditWidget::updateDescriptionLabel);
        connect(temperatureSensorX, &temperatureCsensor::minValueChanged, this, &TemperatureCEditWidget::updateMinValueLabel);
        connect(temperatureSensorX, &temperatureCsensor::maxValueChanged, this, &TemperatureCEditWidget::updateMaxValueLabel);

        connect(temperatureSensorX, &temperatureCsensor::resistanceChanged, this, &TemperatureCEditWidget::updateResistanceLabel);

        connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TemperatureCEditWidget::checkMinSpinBox);
        connect(maxValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TemperatureCEditWidget::checkMaxSpinBox);
    }
}

void TemperatureCEditWidget::updateSensor() {
    if (temperatureSensorX) {
        QString newName = nameLineEdit->text();
        if (newName.isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
                return;
        }
        QString newDescription = descriptionLineEdit->text();
        double newMinValue = minValueSpinBox->value();
        double newMaxValue = maxValueSpinBox->value();
        double newResistance = resistanceSpinBox->value();

        temperatureSensorX->setName(newName);
        temperatureSensorX->setDescription(newDescription);
        temperatureSensorX->setMinValue(newMinValue);
        temperatureSensorX->setMaxValue(newMaxValue);
        temperatureSensorX->setResistance(newResistance);
    }
}

void TemperatureCEditWidget::updateWidget(){
    return;
}

void TemperatureCEditWidget::checkMinSpinBox(double value) {
    if (value >= maxValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima.");
        minValueSpinBox->setValue(maxValueSpinBox->value()-1);
    }
}

void TemperatureCEditWidget::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione massima deve essere superiore alla minima.");
        maxValueSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

}
