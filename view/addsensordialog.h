#ifndef ADDSENSORDIALOG_H
#define ADDSENSORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>

class AddSensorDialog : public QDialog {
    Q_OBJECT

public:
    AddSensorDialog(QWidget *parent = nullptr);

    QString getSensorName() const;
    QString getDescription() const;
    double getMinValue() const;
    double getMaxValue() const;
    int getRange() const;
    QString getSensorType() const;
    double getMassSpinBox() const;
    double getVolumeSpinBox() const;
    double getResistanceSpinBox() const;
    int getCurrentIndex() const;

private slots:
    void updateLayout(int index);
    void checkMinSpinBox(double value);
    void checkMaxSpinBox(double value);
    void checkRangeSpinBox(int value);

    void checkNameLineEdit();

private:
    int currentIndex;

    QDialogButtonBox *buttonBox;
    QPushButton *okButton;
    QPushButton *cancelButton;

    QLineEdit *nameLineEdit;
    QLineEdit *descriptionLineEdit;
    QDoubleSpinBox *minValueSpinBox;
    QDoubleSpinBox *maxValueSpinBox;
    QSpinBox *rangeSpinBox;
    QComboBox *sensorType;

    QFormLayout *formLayout;

    QDoubleSpinBox *massSpinBox;
    QDoubleSpinBox *volumeSpinBox;
    QDoubleSpinBox *resistanceSpinBox;
};

#endif // ADDSENSORDIALOG_H
