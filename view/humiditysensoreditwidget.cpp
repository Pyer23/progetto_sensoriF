#include "humiditysensoreditwidget.h"

namespace sensor {

HumiditySensorEditWidget::HumiditySensorEditWidget(QWidget *parent) : BaseHumiditySensorWidget(parent),
    humiditySensorX(nullptr) {

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

    volumeSpinBox = new QDoubleSpinBox(this);
    volumeSpinBox->setMinimum(0.0);
    volumeSpinBox->setMaximum(1000.0);

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
    formLayout->addWidget(new QLabel("Volume:", this));
    formLayout->addWidget(volumeLabel);
    formLayout->addWidget(volumeSpinBox);
    formLayout->addWidget(changeButton);

    connect(changeButton, &QPushButton::clicked, this, &HumiditySensorEditWidget::updateSensor);
}

void HumiditySensorEditWidget::setHumiditySensor(humiditysensor *hum) {
    humiditySensorX = hum;
    if (humiditySensorX) {
        nameLabel->setText(humiditySensorX->getName());
        descriptionLabel->setText(humiditySensorX->getDescription());
        minValueLabel->setText(QString::number(humiditySensorX->getMinValue()));
        maxValueLabel->setText(QString::number(humiditySensorX->getMaxValue()));
        volumeLabel->setText(QString::number(humiditySensorX->getVolume()));

        nameLineEdit->setText(humiditySensorX->getName());
        descriptionLineEdit->setText(humiditySensorX->getDescription());
        minValueSpinBox->setValue(humiditySensorX->getMinValue());
        maxValueSpinBox->setValue(humiditySensorX->getMaxValue());
        volumeSpinBox->setValue(humiditySensorX->getVolume());

        connect(humiditySensorX, &humiditysensor::nameChanged, this, &HumiditySensorEditWidget::updateNameLabel);
        connect(humiditySensorX, &humiditysensor::descriptionChanged, this, &HumiditySensorEditWidget::updateDescriptionLabel);
        connect(humiditySensorX, &humiditysensor::minValueChanged, this, &HumiditySensorEditWidget::updateMinValueLabel);
        connect(humiditySensorX, &humiditysensor::maxValueChanged, this, &HumiditySensorEditWidget::updateMaxValueLabel);

        connect(humiditySensorX, &humiditysensor::volumeChanged, this, &HumiditySensorEditWidget::updateVolumeLabel);

        connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HumiditySensorEditWidget::checkMinSpinBox);
        connect(maxValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HumiditySensorEditWidget::checkMaxSpinBox);
    }
}

void HumiditySensorEditWidget::updateSensor() {
    if (humiditySensorX) {
        QString newName = nameLineEdit->text();
        if (newName.isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
                return;
        }
        QString newDescription = descriptionLineEdit->text();
        double newMinValue = minValueSpinBox->value();
        double newMaxValue = maxValueSpinBox->value();
        double newVolume = volumeSpinBox->value();

        humiditySensorX->setName(newName);
        humiditySensorX->setDescription(newDescription);
        humiditySensorX->setMinValue(newMinValue);
        humiditySensorX->setMaxValue(newMaxValue);
        humiditySensorX->setVolume(newVolume);
    }
}

void HumiditySensorEditWidget::updateWidget(){
    return;
}

void HumiditySensorEditWidget::checkMinSpinBox(double value) {
    if (value >= maxValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima.");
        minValueSpinBox->setValue(maxValueSpinBox->value()-1);
    }
}

void HumiditySensorEditWidget::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione massima deve essere superiore alla minima.");
        maxValueSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

}
