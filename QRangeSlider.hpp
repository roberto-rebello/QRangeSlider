#include <QWidget>

class QRangeSlider : public QWidget
{

    Q_OBJECT

public:
    QRangeSlider(QWidget *parent = nullptr);
    ~QRangeSlider();
    unsigned int minimum() const;
    void setMinimum(const unsigned int minimum);
    unsigned int maximum() const;
    void setMaximum(const unsigned int maximum);
    unsigned int lowValue() const;
    void setLowValue(const unsigned int lowValue);
    unsigned int highValue() const;
    void setHighValue(const unsigned int highValue);
    unsigned int step() const;
    void setStep(const unsigned int step);
    void setRange(const unsigned int minimum, const unsigned int maximum);

private:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    /* Slider size in pixels */
    unsigned int m_sliderSize = 5;

    /* Slider handle size in pixels */
    unsigned int m_handleSize = 13;

    /* Left and Right padding in pixels */
    unsigned int m_padding = 1;

    /* Minmum range value */
    unsigned int m_minimum = 0;

    /* Maximum range value */
    unsigned int m_maximum = 100;

    /* Step value */
    unsigned int m_step = 1;

    /* Value of low handle */
    unsigned int m_lowValue;

    /* Value of high handle */
    unsigned int m_highValue;

signals:
    void rangeChange(unsigned int minimum, unsigned int maximum);
    void lowValueChange(unsigned int lowValue);
    void highValueChange(unsigned int highValue);
};
