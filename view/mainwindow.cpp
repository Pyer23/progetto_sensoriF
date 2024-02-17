#include "mainwindow.h"

#include "sensorsearchwidget.h"

#include <QtWidgets>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *window = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(window);

    sensor::SensorSearchWidget *search = new sensor::SensorSearchWidget(this);

    layout->addWidget(search);

    setCentralWidget(window);
    setWindowTitle("sensOne");
    setWindowIcon(QIcon(":/images/sensone_icon.ico"));
}

MainWindow::~MainWindow()
{
}

