#include "QRangeSlider.hpp"

#include <QPainter>
#include <QMouseEvent>

QRangeSlider::QRangeSlider(QWidget *parent) : QWidget(parent),
                                              m_sliderSize(5),
                                              m_handleSize(13),
                                              m_padding(0),
                                              m_minimum(0),
                                              m_maximum(100)
{
    m_lowValue = m_minimum;
    m_highValue = m_maximum;

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QRangeSlider::~QRangeSlider()
{
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
    painter.drawRoundedRect(m_padding + ((width() - 2 * m_padding) * (m_lowValue - m_minimum) / (m_maximum - m_minimum)) - (m_handleSize / 2),
                            (height() - m_handleSize) / 2,
                            m_handleSize,
                            m_handleSize,
                            2,
                            2);

    // Draw higher handle
    painter.drawRoundedRect(m_padding + ((width() - 2 * m_padding) * (m_highValue - m_minimum) / (m_maximum - m_minimum)) - (m_handleSize / 2),
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