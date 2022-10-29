#include <QWidget>

class QRangeSlider : public QWidget
{

    Q_OBJECT

public:
    QRangeSlider(QWidget *parent = nullptr);
    ~QRangeSlider();
    unsigned int minimum() const;
    unsigned int maximum() const;
    unsigned int lowValue() const;
    unsigned int highValue() const;
    unsigned int step() const;
    void setStep(const unsigned int step);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void setMinimum(const unsigned int minimum);
    void setMaximum(const unsigned int maximum);
    void setLowValue(const unsigned int lowValue);
    void setHighValue(const unsigned int highValue);
    void setRange(const unsigned int minimum, const unsigned int maximum);

signals:
    void rangeChange(unsigned int minimum, unsigned int maximum);
    void lowValueChange(unsigned int lowValue);
    void highValueChange(unsigned int highValue);

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

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

    int m_lastMouseValue = -1;
};
