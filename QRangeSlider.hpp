#include <QWidget>

class QRangeSlider : public QWidget
{

    Q_OBJECT

public:
    QRangeSlider(QWidget *parent = nullptr);
    ~QRangeSlider();

private:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    /* Slider size in pixels */
    unsigned int m_sliderSize;

    /* Slider handle size in pixels */
    unsigned int m_handleSize;

    /* Left and Right padding in pixels */
    unsigned int m_padding;

    /* Minmum range value */
    unsigned int m_minimum;

    /* Maximum range value */
    unsigned int m_maximum;

    /* Value of low handle */
    unsigned int m_lowValue;

    /* Value of high handle */
    unsigned int m_highValue;
};
