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
        emit(minimumChange(m_minimum));
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
        emit(maximumChange(m_maximum));
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
        if (m_lowValue >= m_highValue)
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
        if (m_highValue <= m_lowValue)
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

QSize QRangeSlider::sizeHint() const
{
    return QSize(100 * m_handleSize + 2 * m_padding, 2 * m_handleSize + 2 * m_padding);
}

QSize QRangeSlider::minimumSizeHint() const
{
    return QSize(2 * m_handleSize + 2 * m_padding, 2 * m_handleSize);
}

void QRangeSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->position().y() >= (height() - m_sliderSize) / 2 - m_handleSize && e->position().y() <= (height() - m_sliderSize) / 2 + m_handleSize) // Check if event was on slider
    {
        float mouseX = e->position().x() < 0 ? 0 : e->position().x();
        unsigned int mouseValue = (mouseX / width()) * (m_maximum - m_minimum) + m_minimum;
        m_lastMouseValue = mouseValue;
    }
}

void QRangeSlider::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    m_lastMouseValue = -1;
}

void QRangeSlider::mouseMoveEvent(QMouseEvent *e)
{
    if (m_lastMouseValue != -1)
    {
        float mouseX = e->position().x() < 0 ? 0 : e->position().x();
        unsigned int mouseValue = (mouseX / width()) * (m_maximum - m_minimum) + m_minimum;

        if (m_lastMouseValue >= m_lowValue - 1 && m_lastMouseValue < m_lowValue + 1)
        {
            setLowValue(mouseValue);
        }
        else if (m_lastMouseValue >= m_highValue - 1 && m_lastMouseValue < m_highValue + 1)
        {
            setHighValue(mouseValue);
        }
        else if (m_lastMouseValue < m_highValue && m_lastMouseValue > m_lowValue)
        {
            int deltaValue = (mouseValue - m_lastMouseValue);
            if (deltaValue < 0)
            {
                setLowValue(m_lowValue + deltaValue > m_lowValue ? m_minimum : m_lowValue + deltaValue); // Check fo underflow
                setHighValue(m_highValue + deltaValue);
            }
            else if (deltaValue > 0)
            {
                setLowValue(m_lowValue + deltaValue);
                setHighValue(m_highValue + deltaValue < m_highValue ? m_maximum : m_highValue + deltaValue); // Check fo overflow
            }
        }

        m_lastMouseValue = mouseValue;
    }
}

void QRangeSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

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
    painter.setBrush(QBrush(QColor(0x1E, 0x90, 0xFF)));
    painter.drawRect(m_padding + ((width() - 2 * m_padding) * (m_lowValue - m_minimum) / (m_maximum - m_minimum)),
                     (height() - m_sliderSize) / 2,
                     (width() - 2 * m_padding) * (m_highValue - m_lowValue) / (m_maximum - m_minimum),
                     m_sliderSize);

    // Draw lower handle
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
