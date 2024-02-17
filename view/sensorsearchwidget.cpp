#include "sensorsearchwidget.h"

#include "../model/accelerometer.h"
#include "../model/humidityrhsensor.h"
#include "../model/humiditysensor.h"
#include "../model/temperaturesensor.h"
#include "../model/temperaturecsensor.h"

#include "../json/jsontocontainer.h"

namespace sensor {

SensorSearchWidget::SensorSearchWidget(QWidget *parent) : QStackedWidget(parent) {

    searchWidget = new QWidget(this);

    searchLayout = new QVBoxLayout(searchWidget);

    visitor = new chartvisitor();

    menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *loadAction = fileMenu->addAction("Carica file di sensori");
    QAction *saveAction = fileMenu->addAction("Salva file di sensori");
    QMenu *sensorMenu = menuBar->addMenu("Sensore");
    QAction *addAction = sensorMenu->addAction("Aggiungi nuovo sensore");
    searchLayout->setMenuBar(menuBar);

    searchLineEdit = new QLineEdit(this);
    searchLayout->addWidget(new QLabel("Barra di ricerca:", this));
    searchLayout->addWidget(searchLineEdit);

    sensorListWidget = new QListWidget(this);
    searchLayout->addWidget(new QLabel("Risultati:"));
    searchLayout->addWidget(sensorListWidget);

    removeButton = new QPushButton("Rimuovi sensore selezionato", this);
    removeButton->setStyleSheet("background-color: #FF0000; color: white;");
    addButton = new QPushButton("Aggiungi nuovo sensore", this);
    addButton->setStyleSheet("background-color: #008000; color: white");
    sensorButtonFrame = new QFrame(this);
    sensorButtonFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    sensorButtonFrame->setLineWidth(3);
    sensorButtonFrame->setMidLineWidth(3);
    sensorButtonLayout = new QHBoxLayout(sensorButtonFrame);
    sensorButtonLayout->addWidget(addButton);
    sensorButtonLayout->addWidget(removeButton);
    searchLayout->addWidget(new QLabel("Pulsanti sensore", this));
    searchLayout->addWidget(sensorButtonFrame);

    saveButton = new QPushButton("Salva file di sensori", this);
    loadButton = new QPushButton("Carica file di sensori", this);
    fileButtonFrame = new QFrame(this);
    fileButtonFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    fileButtonFrame->setLineWidth(2);
    fileButtonFrame->setMidLineWidth(2);
    fileButtonLayout = new QHBoxLayout(fileButtonFrame);
    fileButtonLayout->addWidget(saveButton);
    fileButtonLayout->addWidget(loadButton);
    searchLayout->addWidget(new QLabel("Pulsanti file", this));
    searchLayout->addWidget(fileButtonFrame);

    this->addWidget(searchWidget);

    this->setCurrentWidget(searchWidget);

    connect(addAction, &QAction::triggered, this, &SensorSearchWidget::addSensor);
    connect(loadAction, &QAction::triggered, this, &SensorSearchWidget::loadSensorsFromJson);
    connect(saveAction, &QAction::triggered, this, &SensorSearchWidget::saveContainerAsJson);

    connect(searchLineEdit, &QLineEdit::textChanged, this, &SensorSearchWidget::searchSensors);
    connect(removeButton, &QPushButton::clicked, this, &SensorSearchWidget::removeSelectedSensor);
    connect(addButton, &QPushButton::clicked, this, &SensorSearchWidget::addSensor);

    connect(sensorListWidget, &QListWidget::itemClicked, this, &SensorSearchWidget::openSensor);

    connect(saveButton, &QPushButton::clicked, this, &SensorSearchWidget::saveContainerAsJson);
    connect(loadButton, &QPushButton::clicked, this, &SensorSearchWidget::loadSensorsFromJson);
}

void SensorSearchWidget::setSensorContainer(SensorContainer container) {
    sensorContainer = container;
}

void SensorSearchWidget::searchSensors(const QString &text) {
    sensorListWidget->clear();
    sensorMap.clear();
    //if (sensorContainer) {
        std::vector<sensor*> sensors = sensorContainer.findSensorsByName(text);
        for (sensor *s : sensors) {
            accelerometer* a = dynamic_cast<class accelerometer*>(s);
            humiditysensor* h = dynamic_cast<class humiditysensor*>(s);
            humidityRHsensor* hRH = dynamic_cast<class humidityRHsensor*>(s);
            temperaturesensor* t = dynamic_cast<class temperaturesensor*>(s);
            temperatureCsensor* tC = dynamic_cast<class temperatureCsensor*>(s);

            QString nome = "Nome: ";
            QString stringItem = nome.append(s->getName());

            if(a){
                stringItem.append("   ").append("Tipologia: accelerometro");
            }
            if(h){
                stringItem.append("   ").append("Tipologia: sensore di umidità");
            }
            if(hRH){
                stringItem.append("   ").append("Classificazione: umidità relativa");
            }
            if(t){
                stringItem.append("   ").append("Tipologia: sensore di temperatura");
            }
            if(tC){
                stringItem.append("   ").append("Classificazione: temperatura a contatto");
            }
            QListWidgetItem *item = new QListWidgetItem(stringItem);
            sensorListWidget->addItem(item);
            sensorMap[item] = s;
        }
    //}
}

void SensorSearchWidget::addSensor() {
    /*if (!sensorContainer) {
        qDebug() << "Container dei sensori non impostato!";
        return;
    }
    if (!sensorContainer) {
        qDebug() << "Container dei sensori non impostato!";
        return;
    }*/

    dialog = new AddSensorDialog(this);
    if (dialog->exec() == QDialog::Accepted) {

        index = dialog->getCurrentIndex();

        if (index == 0) {
            name = dialog->getSensorName();
            description = dialog->getDescription();
            range = dialog->getRange();
            minValue = dialog->getMinValue();
            maxValue = dialog->getMaxValue();
            mass = dialog->getMassSpinBox();
            accelerometer *newSensor = new accelerometer(name, description, range, minValue, maxValue, mass);

            sensorContainer.addSensor(newSensor);

            searchSensors(searchLineEdit->text());
        }

        if (index == 1) {
            name = dialog->getSensorName();
            description = dialog->getDescription();
            range = dialog->getRange();
            minValue = dialog->getMinValue();
            maxValue = dialog->getMaxValue();
            volume = dialog->getVolumeSpinBox();
            humiditysensor *newSensor = new humiditysensor(name, description, range, minValue, maxValue, volume);

            sensorContainer.addSensor(newSensor);

            searchSensors(searchLineEdit->text());
        }

        if (index == 2) {
            name = dialog->getSensorName();
            description = dialog->getDescription();
            range = dialog->getRange();
            minValue = dialog->getMinValue();
            maxValue = dialog->getMaxValue();
            volume = dialog->getVolumeSpinBox();
            humidityRHsensor *newSensor = new humidityRHsensor(name, description, range, minValue, maxValue, volume);

            sensorContainer.addSensor(newSensor);

            searchSensors(searchLineEdit->text());
        }

        if (index == 3) {
            name = dialog->getSensorName();
            description = dialog->getDescription();
            range = dialog->getRange();
            minValue = dialog->getMinValue();
            maxValue = dialog->getMaxValue();
            temperaturesensor *newSensor = new temperaturesensor(name, description, range, minValue, maxValue);

            sensorContainer.addSensor(newSensor);

            searchSensors(searchLineEdit->text());
        }

        if (index == 4) {
            name = dialog->getSensorName();
            description = dialog->getDescription();
            range = dialog->getRange();
            minValue = dialog->getMinValue();
            maxValue = dialog->getMaxValue();
            resistance = dialog->getResistanceSpinBox();
            temperatureCsensor *newSensor = new temperatureCsensor(name, description, range, minValue, maxValue, resistance);

            sensorContainer.addSensor(newSensor);

            searchSensors(searchLineEdit->text());
        }

    }

}

void SensorSearchWidget::removeSelectedSensor() {
    QListWidgetItem* selectedItem = sensorListWidget->currentItem();
    if (!selectedItem) {
        qDebug() << "Nessun sensore selezionato.";
        return;
    }

    sensor *s = sensorMap.value(selectedItem, nullptr);
    if (!s) {
        qDebug() << "Nessun sensore corrispondente trovato.";
        return;
    }

    //if (sensorContainer) {
        sensorContainer.removeSensor(s);
        delete s;
        delete sensorListWidget->takeItem(sensorListWidget->row(selectedItem));

        qDebug() << "Sensore rimosso:" << sensorContainer.size();
    //}
}

void SensorSearchWidget::openSensor(QListWidgetItem *item) {

    sensor *s = sensorMap.value(item, nullptr);
    sensorWidget = new QWidget(this);
    sensorLayout = new QVBoxLayout(sensorWidget);
    searchButton = new QPushButton("Torna alla pagina di ricerca", this);

    connect(searchButton, &QPushButton::clicked, this, &SensorSearchWidget::backToSearch);

    if (accelerometer* accSensor = dynamic_cast<accelerometer*>(s)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Nuovo sensore");
        msgBox.setText("Vuoi aprire il sensore selezionato?");
        msgBox.setWindowIcon(QIcon(":/images/sensone_icon.ico"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        msgBox.button(QMessageBox::Yes)->setText("Aprire");
        msgBox.button(QMessageBox::No)->setText("Annulla");

        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            visitor->visit(accSensor);
            sensorLayout->addWidget(visitor->getWidget());
            sensorLayout->addWidget(searchButton);
            this->addWidget(sensorWidget);
            this->setCurrentWidget(sensorWidget);

            searchLineEdit->clear();
        }

    }
    if (humiditysensor* humiditySensor = dynamic_cast<humiditysensor*>(s)) {
        if (humidityRHsensor* humidityRHSensor = dynamic_cast<humidityRHsensor*>(s)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Nuovo sensore");
            msgBox.setWindowIcon(QIcon(":/images/sensone_icon.ico"));
            msgBox.setText("Vuoi aprire il sensore selezionato?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            msgBox.button(QMessageBox::Yes)->setText("Aprire");
            msgBox.button(QMessageBox::No)->setText("Annulla");

            int reply = msgBox.exec();

            if (reply == QMessageBox::Yes) {
                visitor->visit(humidityRHSensor);
                sensorLayout->addWidget(visitor->getWidget());
                sensorLayout->addWidget(searchButton);
                this->addWidget(sensorWidget);
                this->setCurrentWidget(sensorWidget);

                searchLineEdit->clear();
            }

        }else{

            QMessageBox msgBox;
            msgBox.setWindowTitle("Nuovo sensore");
            msgBox.setWindowIcon(QIcon(":/images/sensone_icon.ico"));
            msgBox.setText("Vuoi aprire il sensore selezionato?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            msgBox.button(QMessageBox::Yes)->setText("Aprire");
            msgBox.button(QMessageBox::No)->setText("Annulla");

            int reply = msgBox.exec();

            if (reply == QMessageBox::Yes) {
                visitor->visit(humiditySensor);
                sensorLayout->addWidget(visitor->getWidget());
                sensorLayout->addWidget(searchButton);
                this->addWidget(sensorWidget);
                this->setCurrentWidget(sensorWidget);

                searchLineEdit->clear();
            }
        }

    }

    if (temperaturesensor* temperatureSensor = dynamic_cast<temperaturesensor*>(s)) {
        if (temperatureCsensor* temperatureCSensor = dynamic_cast<temperatureCsensor*>(s)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Nuovo sensore");
            msgBox.setWindowIcon(QIcon(":/images/sensone_icon.ico"));
            msgBox.setText("Vuoi aprire il sensore selezionato?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            msgBox.button(QMessageBox::Yes)->setText("Aprire");
            msgBox.button(QMessageBox::No)->setText("Annulla");

            int reply = msgBox.exec();

            if (reply == QMessageBox::Yes) {
                visitor->visit(temperatureCSensor);
                sensorLayout->addWidget(visitor->getWidget());
                sensorLayout->addWidget(searchButton);
                this->addWidget(sensorWidget);
                this->setCurrentWidget(sensorWidget);

                searchLineEdit->clear();
            }

        }else{

            QMessageBox msgBox;
            msgBox.setWindowTitle("Nuovo sensore");
            msgBox.setWindowIcon(QIcon(":/images/sensone_icon.ico"));
            msgBox.setText("Vuoi aprire il sensore selezionato?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            msgBox.button(QMessageBox::Yes)->setText("Aprire");
            msgBox.button(QMessageBox::No)->setText("Annulla");

            int reply = msgBox.exec();

            if (reply == QMessageBox::Yes) {
                visitor->visit(temperatureSensor);
                sensorLayout->addWidget(visitor->getWidget());
                sensorLayout->addWidget(searchButton);
                this->addWidget(sensorWidget);
                this->setCurrentWidget(sensorWidget);

                searchLineEdit->clear();

            }
        }

    }

}

void SensorSearchWidget::backToSearch(){
    this->setCurrentWidget(searchWidget);
}

void SensorSearchWidget::saveContainerAsJson() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Sensor Container"), "", tr("JSON Files (*.json)"));
    containerToJson.saveToJson(sensorContainer, filePath);

    QFile file(filePath);
    bool success = file.exists();
    if (success) {
        //qDebug() << "Il contenitore è stato salvato correttamente.";
    } else {
        //qDebug() << "Il contenitore non è stato salavato, si è verificato un errore durante il salvataggio del contenitore.";
    }
}

void SensorSearchWidget::loadSensorsFromJson() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("File JSON (*.json)"));
    if (!filePath.isEmpty()) {
        JsonToContainer converter;

        QJsonObject json = converter.loadFromJsonFile(filePath);

        SensorContainer container = converter.convertJsonToContainer(filePath);

        this->setSensorContainer(container);

        searchLineEdit->clear();
    }
}

}
