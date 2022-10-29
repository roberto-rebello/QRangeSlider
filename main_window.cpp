#include "main_window.hpp"

#include "QRangeSlider.hpp"

#include <QSlider>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("QRangeSlider Demo");

    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *container = new QWidget(this);
    container->setLayout(layout);
    setCentralWidget(container);

    QSlider *slider = new QSlider(Qt::Orientation::Horizontal);
    layout->addWidget(slider);

    QRangeSlider *qRangeSlider = new QRangeSlider();
    layout->addWidget(qRangeSlider);
}