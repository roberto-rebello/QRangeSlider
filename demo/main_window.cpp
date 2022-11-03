#include "main_window.hpp"

#include "../src/QRangeSlider.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("QRangeSlider Demo");
    setMinimumSize(500, 100);

    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *container = new QWidget(this);
    container->setLayout(layout);
    setCentralWidget(container);

    QSpinBox *minimum = new QSpinBox();
    minimum->setRange(0, 200);
    QSpinBox *maximum = new QSpinBox();
    maximum->setRange(0, 200);
    QSpinBox *lowValue = new QSpinBox();
    lowValue->setRange(0, 100);
    QSpinBox *highValue = new QSpinBox();
    highValue->setRange(0, 100);
    QHBoxLayout *valuesLayout = new QHBoxLayout();
    valuesLayout->addWidget(minimum);
    valuesLayout->addWidget(lowValue);
    valuesLayout->addWidget(highValue);
    valuesLayout->addWidget(maximum);
    layout->addLayout(valuesLayout);

    QRangeSlider *qRangeSlider = new QRangeSlider();
    qRangeSlider->setRange(0, 100);
    qRangeSlider->setLowValue(10);
    qRangeSlider->setHighValue(90);
    layout->addWidget(qRangeSlider);

    minimum->setValue(qRangeSlider->minimum());
    lowValue->setValue(qRangeSlider->lowValue());
    highValue->setValue(qRangeSlider->highValue());
    maximum->setValue(qRangeSlider->maximum());

    // QRangeSlider Values
    connect(minimum, &QSpinBox::valueChanged, qRangeSlider, &QRangeSlider::setMinimum);
    connect(lowValue, &QSpinBox::valueChanged, qRangeSlider, &QRangeSlider::setLowValue);
    connect(highValue, &QSpinBox::valueChanged, qRangeSlider, &QRangeSlider::setHighValue);
    connect(maximum, &QSpinBox::valueChanged, qRangeSlider, &QRangeSlider::setMaximum);

    // QRangeSlider updade signals
    connect(qRangeSlider, &QRangeSlider::minimumChange, minimum, &QSpinBox::setValue);
    connect(qRangeSlider, &QRangeSlider::lowValueChange, lowValue, &QSpinBox::setValue);
    connect(qRangeSlider, &QRangeSlider::highValueChange, highValue, &QSpinBox::setValue);
    connect(qRangeSlider, &QRangeSlider::maximumChange, maximum, &QSpinBox::setValue);

    connect(qRangeSlider, &QRangeSlider::rangeChange, lowValue, &QSpinBox::setRange);
    connect(qRangeSlider, &QRangeSlider::rangeChange, highValue, &QSpinBox::setRange);

    QPushButton *reset = new QPushButton("Reset");
    layout->addWidget(reset);
    connect(reset, &QPushButton::clicked, qRangeSlider, [qRangeSlider]
            { qRangeSlider->setRange(0, 100); });
    connect(reset, &QPushButton::clicked, lowValue, [lowValue]
            { lowValue->setValue(10); });
    connect(reset, &QPushButton::clicked, highValue, [highValue]
            { highValue->setValue(90); });
}