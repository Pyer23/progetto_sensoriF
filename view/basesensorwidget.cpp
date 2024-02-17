#include "basesensorwidget.h"

namespace sensor {

BaseSensorWidget::BaseSensorWidget(QWidget *parent) : QWidget(parent) {
    nameLabel = new QLabel(this);
    descriptionLabel = new QLabel(this);
    minValueLabel = new QLabel(this);
    maxValueLabel = new QLabel(this);
}

void BaseSensorWidget::updateNameLabel(const QString &name) {
    nameLabel->setText(name);
}

void BaseSensorWidget::updateDescriptionLabel(const QString &description) {
    descriptionLabel->setText(description);
}

void BaseSensorWidget::updateMinValueLabel(const double &minValue) {
    minValueLabel->setText(QString::number(minValue));
}

void BaseSensorWidget::updateMaxValueLabel(const double &maxValue) {
    maxValueLabel->setText(QString::number(maxValue));
}

}
