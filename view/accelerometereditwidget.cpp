#include "accelerometereditwidget.h"

namespace sensor {

AccelerometerEditWidget::AccelerometerEditWidget(QWidget *parent) : BaseAccelerometerWidget(parent),
    accelerometerX(nullptr) {

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

    massSpinBox = new QDoubleSpinBox(this);
    massSpinBox->setMinimum(0.0);
    massSpinBox->setMaximum(1000.0);

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
    formLayout->addWidget(new QLabel("Massa:", this));
    formLayout->addWidget(massLabel);
    formLayout->addWidget(massSpinBox);
    formLayout->addWidget(changeButton);

    connect(changeButton, &QPushButton::clicked, this, &AccelerometerEditWidget::updateSensor);
}

void AccelerometerEditWidget::setAccelerometer(accelerometer *acc) {
    accelerometerX = acc;
    if (accelerometerX) {
        nameLabel->setText(accelerometerX->getName());
        descriptionLabel->setText(accelerometerX->getDescription());
        minValueLabel->setText(QString::number(accelerometerX->getMinValue()));
        maxValueLabel->setText(QString::number(accelerometerX->getMaxValue()));
        massLabel->setText(QString::number(accelerometerX->getMass()));

        nameLineEdit->setText(accelerometerX->getName());
        descriptionLineEdit->setText(accelerometerX->getDescription());
        minValueSpinBox->setValue(accelerometerX->getMinValue());
        maxValueSpinBox->setValue(accelerometerX->getMaxValue());
        massSpinBox->setValue(accelerometerX->getMass());

        connect(accelerometerX, &accelerometer::nameChanged, this, &AccelerometerEditWidget::updateNameLabel);
        connect(accelerometerX, &accelerometer::descriptionChanged, this, &AccelerometerEditWidget::updateDescriptionLabel);
        connect(accelerometerX, &accelerometer::minValueChanged, this, &AccelerometerEditWidget::updateMinValueLabel);
        connect(accelerometerX, &accelerometer::maxValueChanged, this, &AccelerometerEditWidget::updateMaxValueLabel);

        connect(accelerometerX, &accelerometer::massChanged, this, &AccelerometerEditWidget::updateMassLabel);

        connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AccelerometerEditWidget::checkMinSpinBox);
        connect(maxValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AccelerometerEditWidget::checkMaxSpinBox);
    }
}

void AccelerometerEditWidget::updateSensor() {
    if (accelerometerX) {
        QString newName = nameLineEdit->text();
        if (newName.isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
            return;
        }
        QString newDescription = descriptionLineEdit->text();
        double newMinValue = minValueSpinBox->value();
        double newMaxValue = maxValueSpinBox->value();
        double newMass = massSpinBox->value();

        accelerometerX->setName(newName);
        accelerometerX->setDescription(newDescription);
        accelerometerX->setMinValue(newMinValue);
        accelerometerX->setMaxValue(newMaxValue);
        accelerometerX->setMass(newMass);
    }
}

void AccelerometerEditWidget::updateWidget(){
    return;
}

void AccelerometerEditWidget::checkMinSpinBox(double value) {
    if (value >= maxValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima.");
        minValueSpinBox->setValue(maxValueSpinBox->value()-1);
    }
}

void AccelerometerEditWidget::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione massima deve essere superiore alla minima.");
        maxValueSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

}
