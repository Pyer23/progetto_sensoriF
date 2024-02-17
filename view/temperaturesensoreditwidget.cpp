#include "temperaturesensoreditwidget.h"

namespace sensor {

TemperatureSensorEditWidget::TemperatureSensorEditWidget(QWidget *parent) : BaseSensorWidget(parent),
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

    formLayout->addWidget(changeButton);

    connect(changeButton, &QPushButton::clicked, this, &TemperatureSensorEditWidget::updateSensor);
}

void TemperatureSensorEditWidget::setTemperatureSensor(temperaturesensor *temp) {
    temperatureSensorX = temp;
    if (temperatureSensorX) {
        nameLabel->setText(temperatureSensorX->getName());
        descriptionLabel->setText(temperatureSensorX->getDescription());
        minValueLabel->setText(QString::number(temperatureSensorX->getMinValue()));
        maxValueLabel->setText(QString::number(temperatureSensorX->getMaxValue()));

        nameLineEdit->setText(temperatureSensorX->getName());
        descriptionLineEdit->setText(temperatureSensorX->getDescription());
        minValueSpinBox->setValue(temperatureSensorX->getMinValue());
        maxValueSpinBox->setValue(temperatureSensorX->getMaxValue());

        connect(temperatureSensorX, &temperaturesensor::nameChanged, this, &TemperatureSensorEditWidget::updateNameLabel);
        connect(temperatureSensorX, &temperaturesensor::descriptionChanged, this, &TemperatureSensorEditWidget::updateDescriptionLabel);
        connect(temperatureSensorX, &temperaturesensor::minValueChanged, this, &TemperatureSensorEditWidget::updateMinValueLabel);
        connect(temperatureSensorX, &temperaturesensor::maxValueChanged, this, &TemperatureSensorEditWidget::updateMaxValueLabel);

        connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TemperatureSensorEditWidget::checkMinSpinBox);
        connect(maxValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TemperatureSensorEditWidget::checkMaxSpinBox);
    }
}

void TemperatureSensorEditWidget::updateSensor() {
    if (temperatureSensorX) {
        QString newName = nameLineEdit->text();
        if (newName.isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
                return;
        }
        QString newDescription = descriptionLineEdit->text();
        double newMinValue = minValueSpinBox->value();
        double newMaxValue = maxValueSpinBox->value();

        temperatureSensorX->setName(newName);
        temperatureSensorX->setDescription(newDescription);
        temperatureSensorX->setMinValue(newMinValue);
        temperatureSensorX->setMaxValue(newMaxValue);
    }
}

void TemperatureSensorEditWidget::updateWidget(){
    return;
}

void TemperatureSensorEditWidget::checkMinSpinBox(double value) {
    if (value >= maxValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima.");
        minValueSpinBox->setValue(maxValueSpinBox->value()-1);
    }
}

void TemperatureSensorEditWidget::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione massima deve essere superiore alla minima.");
        maxValueSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

}

