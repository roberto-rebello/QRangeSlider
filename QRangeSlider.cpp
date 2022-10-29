#include "QRangeSlider.hpp"

#include <QPainter>
#include <QMouseEvent>

QRangeSlider::QRangeSlider(QWidget *parent) : QWidget(parent)
{
    m_lowValue = m_minimum;
    m_highValue = m_maximum;

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QRangeSlider::~QRangeSlider()
{
}

unsigned int QRangeSlider::minimum() const
{
    return m_minimum;
}

void QRangeSlider::setMinimum(const unsigned int minimum)
{
    if (m_minimum != minimum)
    {
        m_minimum = minimum;
        if (m_minimum >= m_maximum)
        {
            setMaximum(m_minimum + 1);
            setHighValue(m_maximum);
            setLowValue(m_minimum);
        }
        else if (m_minimum >= m_highValue)
        {
            setHighValue(m_minimum + 1);
            setLowValue(m_minimum);
        }
        else if (m_minimum > m_lowValue)
        {
            setLowValue(m_minimum);
        }

        update();
        emit(rangeChange(m_minimum, m_maximum));
    }
}

unsigned int QRangeSlider::maximum() const
{
    return m_maximum;
}

void QRangeSlider::setMaximum(const unsigned int maximum)
{
    if (maximum != m_maximum)
    {
        m_maximum = maximum;
        if (m_maximum <= m_minimum)
        {
            setMinimum(m_maximum++);
            setHighValue(m_maximum);
            setLowValue(m_minimum);
        }
        else if (m_maximum <= m_lowValue)
        {
            setHighValue(m_maximum);
            setLowValue(m_highValue - 1);
        }
        else if (m_maximum < m_highValue)
        {
            setHighValue(m_maximum);
        }

        update();
        emit(rangeChange(m_minimum, m_maximum));
    }
}

unsigned int QRangeSlider::lowValue() const
{
    return m_lowValue;
}

void QRangeSlider::setLowValue(const unsigned int lowValue)
{
    if (m_lowValue != lowValue)
    {
        m_lowValue = lowValue;
        if (m_lowValue > m_maximum)
        {
            m_lowValue = m_maximum - 1;
        }
        if (m_lowValue < m_minimum)
        {
            m_lowValue = m_minimum;
        }
        if (m_lowValue > m_highValue)
        {
            setHighValue(m_lowValue + 1);
        }

        update();
        emit(lowValueChange(m_lowValue));
    }
}

unsigned int QRangeSlider::highValue() const
{
    return m_highValue;
}

void QRangeSlider::setHighValue(const unsigned int highValue)
{
    if (m_highValue != highValue)
    {
        m_highValue = highValue;
        if (m_highValue > m_maximum)
        {
            m_highValue = m_maximum;
        }
        if (m_highValue < m_minimum)
        {
            m_highValue = m_minimum + 1;
        }
        if (m_highValue < m_lowValue)
        {
            setLowValue(m_lowValue - 1);
        }

        update();
        emit(highValueChange(m_highValue));
    }
}

unsigned int QRangeSlider::step() const
{
    return m_step;
}

void QRangeSlider::setStep(const unsigned int step)
{
    m_step = step;
}

void QRangeSlider::setRange(const unsigned int minimum, const unsigned int maximum)
{
    setMinimum(minimum);
    setMaximum(maximum);
}

void QRangeSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    painter.fillRect(0, 0, width(), height(), Qt::GlobalColor::green);

    // Draw background
    painter.setPen(QPen(Qt::GlobalColor::darkGray, 0.8));
    painter.setBrush(QBrush(QColor(Qt::GlobalColor::lightGray)));
    painter.drawRoundedRect(m_padding,
                            (height() - m_sliderSize) / 2,
                            width() - 2 * m_padding,
                            m_sliderSize,
                            2,
                            2);

    // Draw range
    painter.setPen(QPen(Qt::GlobalColor::darkBlue, 0.8));
    painter.setBrush(QBrush(QColor(Qt::GlobalColor::blue)));
    painter.drawRect(m_padding + ((width() - 2 * m_padding) * (m_lowValue - m_minimum) / (m_maximum - m_minimum)),
                     (height() - m_sliderSize) / 2,
                     (width() - 2 * m_padding) * (m_highValue - m_lowValue) / (m_maximum - m_minimum),
                     m_sliderSize);

    // Draw lower handle
    painter.setPen(QPen(Qt::GlobalColor::darkGray, 0.8));
    painter.setBrush(QBrush(QColor(Qt::GlobalColor::white)));
    painter.drawRoundedRect(m_padding + ((width() - 2 * m_padding) * (m_lowValue - m_minimum) / (m_maximum - m_minimum)),
                            (height() - m_handleSize) / 2,
                            m_handleSize,
                            m_handleSize,
                            2,
                            2);

    // Draw higher handle
    painter.drawRoundedRect(m_padding + ((width() - 2 * m_padding) * (m_highValue - m_minimum) / (m_maximum - m_minimum)) - m_handleSize,
                            (height() - m_handleSize) / 2,
                            m_handleSize,
                            m_handleSize,
                            2,
                            2);

    painter.end();
}

QSize QRangeSlider::sizeHint() const
{
    return QSize(2 * m_handleSize + 2 * m_padding, m_handleSize + 2 * m_padding);
}

QSize QRangeSlider::minimumSizeHint() const
{
    return QSize(2 * m_handleSize + 2 * m_padding, m_handleSize);
}