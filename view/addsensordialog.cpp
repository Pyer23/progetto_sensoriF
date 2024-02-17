#include "addsensordialog.h"

AddSensorDialog::AddSensorDialog(QWidget *parent) : QDialog(parent) {

    nameLineEdit = new QLineEdit(this);
    descriptionLineEdit = new QLineEdit(this);

    minValueSpinBox = new QDoubleSpinBox(this);
    minValueSpinBox->setMinimum(-1000.0);
    minValueSpinBox->setMaximum(999.0);
    maxValueSpinBox = new QDoubleSpinBox(this);
    maxValueSpinBox->setMinimum(-999.0);
    maxValueSpinBox->setMaximum(1000.0);
    maxValueSpinBox->setValue(1.0);

    rangeSpinBox = new QSpinBox(this);
    rangeSpinBox->setValue(2);

    sensorType = new QComboBox(this);
    sensorType->addItem("Accelerometro");
    sensorType->addItem("Sensore di umidità");
    sensorType->addItem("Sensore di umidità relativa");
    sensorType->addItem("Sensore di temperatura");
    sensorType->addItem("Sensore di temperatura a contatto");

    formLayout = new QFormLayout(this);
    formLayout->addRow(new QLabel("Nome:", this));
    formLayout->addRow(nameLineEdit);
    formLayout->addRow(new QLabel("Descrizone:", this));
    formLayout->addRow(descriptionLineEdit);
    formLayout->addRow(new QLabel("Minima rilevazione:", this));
    formLayout->addRow(minValueSpinBox);
    formLayout->addRow(new QLabel("Massima rilevazione:", this));
    formLayout->addRow(maxValueSpinBox);
    formLayout->addRow(new QLabel("Range di osservazione:", this));
    formLayout->addRow(rangeSpinBox);
    formLayout->addRow(new QLabel("Classificazione:", this));
    formLayout->addRow(sensorType);

    connect(minValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AddSensorDialog::checkMinSpinBox);
    connect(maxValueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AddSensorDialog::checkMaxSpinBox);
    connect(rangeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &AddSensorDialog::checkRangeSpinBox);

    connect(sensorType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddSensorDialog::updateLayout);

    setWindowTitle("sensOne");

    updateLayout(0);

}

void AddSensorDialog::updateLayout(int index){
    if (formLayout) {
        while(formLayout->count() > 12){
            QLayoutItem *item = formLayout->takeAt(12);
            delete item->widget();
            delete item;
        }

        buttonBox = new QDialogButtonBox(Qt::Horizontal, this);

        okButton = new QPushButton("Aggiungi sensore", this);
        cancelButton = new QPushButton("Annulla", this);

        buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
        buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(okButton, &QPushButton::clicked, this, &AddSensorDialog::checkNameLineEdit);

        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        if (index == 0) {
            formLayout->addRow(new QLabel("Massa:"));
            massSpinBox = new QDoubleSpinBox(this);
            massSpinBox->setMinimum(0.0);
            massSpinBox->setMaximum(1000.0);
            formLayout->addRow(massSpinBox);
            formLayout->addRow(buttonBox);

            currentIndex = 0;

        } else if (index == 1) {
            formLayout->addRow(new QLabel("Volume:"));
            volumeSpinBox = new QDoubleSpinBox(this);
            volumeSpinBox->setMinimum(0.0);
            volumeSpinBox->setMaximum(1000.0);
            formLayout->addRow(volumeSpinBox);
            formLayout->addRow(buttonBox);

            currentIndex = 1;

        } else if(index == 2) {
            formLayout->addRow(new QLabel("Volume:"));
            volumeSpinBox = new QDoubleSpinBox(this);
            volumeSpinBox->setMinimum(0.0);
            volumeSpinBox->setMaximum(1000.0);
            formLayout->addRow(volumeSpinBox);
            formLayout->addRow(new QLabel("Nei sensori di umidità relativa la massima saturazione corrisponde alla massima rilevazione del sensore, poichè corrisponde alla massima quantità di vapore acqueo rilevabile."));
            formLayout->addRow(buttonBox);

            currentIndex = 2;

        } else if (index == 3) {
            formLayout->addRow(new QLabel("Nei sensori di temperatura normali non ci sono ulteriori variabili."));
            formLayout->addRow(buttonBox);

            currentIndex = 3;

        } else if (index == 4) {
            formLayout->addRow(new QLabel("Resistenza:"));
            resistanceSpinBox = new QDoubleSpinBox(this);
            resistanceSpinBox->setMinimum(0.0);
            resistanceSpinBox->setMaximum(1000.0);
            formLayout->addRow(resistanceSpinBox);
            formLayout->addRow(buttonBox);

            currentIndex = 4;

        }
    }
}

void AddSensorDialog::checkMinSpinBox(double value) {
    if (value >= maxValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione minima deve essere inferiore alla massima.");
        minValueSpinBox->setValue(maxValueSpinBox->value()-1);
    }
}

void AddSensorDialog::checkMaxSpinBox(double value) {
    if (value <= minValueSpinBox->value()) {
        QMessageBox::warning(this, "Valore inserito non valido", "La rilevazione massima deve essere superiore alla minima.");
            maxValueSpinBox->setValue(minValueSpinBox->value()+1);
    }
}

void AddSensorDialog::checkRangeSpinBox(int value) {
    if (value < 2 || value > 99) {
            QMessageBox::warning(this, "Valore inserito non valido", "Il range di osservazione ha un valore minimo di 2 e un massimo di 99.");
            rangeSpinBox->setValue(2);
    }
}

void AddSensorDialog::checkNameLineEdit() {
    if (nameLineEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Campo nome vuoto", "Il campo nome non può essere vuoto. Per favore inserisci un nome per il sensore.");
            QDialog::reject();
            return;
    }else{
            QDialog::accept();
    }
}

QString AddSensorDialog::getSensorName() const {
    return nameLineEdit->text();
}

QString AddSensorDialog::getDescription() const {
    return descriptionLineEdit->text();
}

double AddSensorDialog::getMinValue() const {
    return minValueSpinBox->value();
}

double AddSensorDialog::getMaxValue() const {
    return maxValueSpinBox->value();
}

int AddSensorDialog::getRange() const {
    return rangeSpinBox->value();
}

QString AddSensorDialog::getSensorType() const {
    return sensorType->currentText();
}

double AddSensorDialog::getMassSpinBox() const {
    return massSpinBox->value();
}

double AddSensorDialog::getVolumeSpinBox() const {
    return volumeSpinBox->value();
}

double AddSensorDialog::getResistanceSpinBox() const {
    return resistanceSpinBox->value();
}

int AddSensorDialog::getCurrentIndex() const {
    return currentIndex;
}
