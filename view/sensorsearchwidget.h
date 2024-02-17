#ifndef SENSORSEARCHWIDGET_H
#define SENSORSEARCHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QInputDialog>
#include <QComboBox>
#include <QMap>
#include <QDialogButtonBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QMenuBar>

#include "addsensordialog.h"
#include "../model/sensorcontainer.h"
#include "chartvisitor.h"

#include "../json/containertojson.h"

namespace sensor {

class SensorSearchWidget : public QStackedWidget {
    Q_OBJECT
public:
    SensorSearchWidget(QWidget *parent = nullptr);
    void setSensorContainer(SensorContainer container);

public slots:
    void saveContainerAsJson();
    void loadSensorsFromJson();

private slots:
    void searchSensors(const QString &text);

    void addSensor();

    void openSensor(QListWidgetItem *item);

    void removeSelectedSensor();

    void backToSearch();

private:
    QMenuBar *menuBar;

    QWidget *searchWidget;
    QWidget *sensorWidget;

    AddSensorDialog *dialog;

    QVBoxLayout *searchLayout;
    QVBoxLayout *sensorLayout;

    QPushButton *searchButton;

    QLineEdit *searchLineEdit;
    QListWidget *sensorListWidget;

    QFrame *sensorButtonFrame;
    QHBoxLayout *sensorButtonLayout;

    QFrame *fileButtonFrame;
    QHBoxLayout *fileButtonLayout;

    QPushButton *removeButton;
    QPushButton *addButton;
    QPushButton *saveButton;
    QPushButton *loadButton;

    SensorContainer sensorContainer;

    QPushButton *openButton;

    chartvisitor *visitor;

    QMap<QListWidgetItem *, sensor *> sensorMap;

    QString name;
    QString description;
    int range;
    double minValue;
    double maxValue;
    int index;

    double mass;
    double volume;
    double resistance;

    ContainerToJson containerToJson;
};

}

#endif // SENSORSEARCHWIDGET_H
