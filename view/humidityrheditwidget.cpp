#include "humidityrheditwidget.h"

namespace sensor {

HumidityRHEditWidget::HumidityRHEditWidget(QWidget *parent) : BaseHumiditySensorWidget(parent),
    humiditySensorX(nullptr) {

    nameLineEdit = new QLineEdit(this);
    descriptionLineEdit = new QLineEdit(this);

    minValueSpinBox = new QDoubleSpinBox(this);
    minValueSpinBox->setMinimum(-1000.0);
    minValueSpinBox->setMaximum(999.0);

    changeButton = new QPushButton("Cambia i parametri modificati", this);

    formLayout = new QFormLayout(this);

    volumeSpinBox = new QDoubleSpinBox(this);
    volumeSpinBox->setMinimum(0.0);
    volumeSpinBox->setMaximum(1000.0);

    maxSaturationSpinBox = new QDoubleSpinBox(this);
    maxSaturationSpinBox->setMinimum(-999.0);
    maxSaturationSpinBox->setMaximum(1000.0);

    formLayout->addWidget(new QLabel("Nome:", this));
    formLayout->addWidget(nameLabel);
    formLayout->addWidget(nameLineEdit);
    formLayout->addWidget(new QLabel("Descrizione:", this));
    formLayout->addWidget(descriptionLabel);
    formLayout->addWidget(descriptionLineEdit);
    formLayout->addWidget(new QLabel("Minima Rilevazione:", this));
    formLayout->addWidget(minValueLabel);
    formLayout->addWidget(minValueSpinBox);
    formLayout->addWidget(new QLabel("Volume:", this));
    formLayout->addWidget(volumeLabel);
    formLayout->addWidget(volumeSpinBox);
    formLayout->addWidget(new QLabel("Massima saturazione:", this));
    formLayout->addWidget(maxSaturationLabel);
    formLayout->addWidget(maxSaturationSpinBox);
    formLayout->addWidget(changeButton);

    connect(changeButton, &QPushButton::clicked, this, &HumidityRHEditWidget::updateSensor);

}

void HumidityRHEditWidget::setHumiditySensor(humidityRHsensor *hum) {
    humiditySensorX = hum;
    if (humiditySensorX) {
        nameLabel->setText(humiditySensorX->getName());
        descriptionLabel->setText(humiditySensorX->getDescription());
        minValueLabel->setText(QString::number(humiditySensorX->getMinValue()));
        volumeLabel->setText(QString::number(humiditySensorX->getVolume()));
        maxSaturationLabel->setText(QString::number(humiditySensorX->getMaxValue()));

        nameLineEdit->setText(humiditySensorX->getName());
        descriptionLineEdit->setText(humiditySensorX->getDescription());
        minValueSpinBox->setValue(humiditySensorX->getMinValue());
        volumeSpinBox->setValue(humiditySensorX->getVolume());
        maxSaturationSpinBox->setValue(humiditySensorX->getMaxValue());

        connect(humiditySensorX, &humidityRHsensor::nameChanged, this, &HumidityRHEditWidget::updateNameLabel);
        connect(humiditySensorX, &humidityRHsensor::descriptionChanged, this, &HumidityRHEditWidget::updateDescriptionLabel);
        connect(humiditySensorX, &humidityRHsensor::minValueChanged, this, &HumidityRHEditWidget::updateMinValueLabel);

        connect(humiditySensorX, &humidityRHsensor::volumeChanged, this, &HumidityRHEditWidget::updateVolumeLabel);
        connect(humiditySensorX, &humidityRHsensor::maxValueChanged, this, &HumidityRHEditWidget::updateMaxSaturationLabel);

        connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HumidityRHEditWidget::checkMinSpinBox);
        connect(maxSaturationSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HumidityRHEditWidget::checkMaxSpinBox);
    }
}

void HumidityRHEditWidget::updateSensor() {
    if (humiditySensorX) {
        QString newName = nameLineEdit->text();
        if (newName.isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
                return;
        }
        QString newDescription = descriptionLineEdit->text();
        double newMinValue = minValueSpinBox->value();
        double newVolume = volumeSpinBox->value();
        double newMaxSaturation = maxSaturationSpinBox->value();

        humiditySensorX->setName(newName);
        humiditySensorX->setDescription(newDescription);
        humiditySensorX->setMinValue(newMinValue);
        humiditySensorX->setVolume(newVolume);
        humiditySensorX->setMaxValue(newMaxSaturation);
    }
}

void HumidityRHEditWidget::updateWidget(){
    return;
}

void HumidityRHEditWidget::checkMinSpinBox(double value) {
    if (value >= maxSaturationSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima saturazione.");
        minValueSpinBox->setValue(maxSaturationSpinBox->value()-1);
    }
}

void HumidityRHEditWidget::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La massima saturazione deve essere superiore alla minima.");
        maxSaturationSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

}
