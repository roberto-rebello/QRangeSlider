from PyQt5.QtCore import pyqtSignal, pyqtSlot, QSize
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QColorConstants, QPen, QBrush, QColor

class QRangeSlider(QWidget):

    # Minimum range value
    _minimum = 0

    # Maximum range value
    _maximum = 100

    # Step value
    _step = 1

    # Value of the last mouse click
    _lastMouseValue = -1

    # Painter constants
    # Slider height in pixels
    SLIDER_HEIGHT = 5
    # Slider handle size in pixels
    HANDLE_SIZE = 13
    # Left and Right padding in pixels
    PADDING = 1

    # Signals
    _minimumChange = pyqtSignal(int)
    _maximumChange = pyqtSignal(int)
    _lowValueChange = pyqtSignal(int)
    _highValueChange = pyqtSignal(int)
    _rangeChange = pyqtSignal(int, int)
    
    def __init__(self, parent = None):
        super().__init__(parent)

        # Value of low handle
        self._lowValue = self._minimum

        # Value of high handle
        self._highValue = self._maximum

    def minimum(self):
        return self._minimum

    @pyqtSlot(int)
    def setMinimum(self, minimum):
        if self._minimum != minimum:
            self._minimum = minimum
            if self._minimum >= self._maximum:
                self.setMaximum(self._minimum + 1)
                self.setHighValue(self._maximum)
                self.setLowValue(self._minimum)
            elif self._minimum >= self._highValue:
                self.setHighValue(self._minimum + 1)
                self.setLowValue(self._minimum)
            elif self._minimum > self._lowValue:
                self.setLowValue(self._minimum)

            self.update()
            self._minimumChange.emit(self._minimum)
            self._rangeChange.emit(self._minimum, self._maximum)

    def maximum(self):
        return self._maximum

    @pyqtSlot(int)
    def setMaximum(self, maximum):
        if self._maximum != maximum:
            self._maximum = maximum
            if self._maximum <= self._minimum:
                self.setMinimum(self._maximum + 1)
                self.setHighValue(self._maximum)
                self.setLowValue(self._minimum)
            elif self._maximum <= self._lowValue:
                self.setHighValue(self._maximum)
                self.setLowValue(self._highValue -1)
            elif self._maximum < self._highValue:
                self.setHighValue(self._maximum)

            self.update()
            self._maximumChange.emit(self._maximum)
            self._rangeChange.emit(self._minimum, self._maximum)

    def lowValue(self):
        return self._lowValue
    
    @pyqtSlot(int)
    def setLowValue(self, lowValue):
        if self._lowValue != lowValue:
            self._lowValue = lowValue
            if self._lowValue > self._maximum:
                self._lowValue = self._maximum - 1
            if self._lowValue < self._minimum:
                self._lowValue = self._minimum
            if self._lowValue >= self._highValue:
                self.setHighValue(self._lowValue + 1)

            self.update()
            self._lowValueChange.emit(self._lowValue)

    def highValue(self):
        return self._highValue
    
    @pyqtSlot(int)
    def setHighValue(self, highValue):
        if self._highValue != highValue:
            self._highValue = highValue
            if self._highValue > self._maximum:
                self._highValue = self._maximum
            if self._highValue < self._minimum:
                self._highValue = self._minimum + 1
            if self._highValue <= self._lowValue:
                self.setLowValue(self._lowValue - 1)

            self.update()
            self._highValueChange.emit(self._highValue)

    def step(self):
        return self._step
    
    def setStep(self, step):
        self._step = step

    @pyqtSlot(int, int)
    def setRange(self, minimum, maximum):
        self.setMinimum(minimum)
        self.setMaximum(maximum)

    def sizeHint(self):
        return QSize(100 * self.HANDLE_SIZE + 2 * self.PADDING, 2 * self.HANDLE_SIZE + 2 * self.PADDING)

    def minimumSizeHint(self):
        return QSize(2 * self.HANDLE_SIZE + 2 * self.PADDING, 2 * self.HANDLE_SIZE)

    def mousePressEvent(self, mouseEvent):
        # Check if event was on slider
        if mouseEvent.pos().y() >= (self.height() - self.SLIDER_HEIGHT - self.HANDLE_SIZE) / 2 and mouseEvent.pos().y() <= (self.height() - self.SLIDER_HEIGHT + self.HANDLE_SIZE) / 2:
            mouseX = 0 if mouseEvent.pos().x() < 0 else mouseEvent.pos().x()
            mouseValue = int((mouseX / self.width()) * (self._maximum - self._minimum) + self._minimum)
            self._lastMouseValue = mouseValue

    def mouseReleaseEvent(self, mouseEvent):
        self._lastMouseValue = -1

    def mouseMoveEvent(self, mouseEvent):
        if self._lastMouseValue != -1:
            mouseX = 0 if mouseEvent.pos().x() < 0 else mouseEvent.pos().x()
            mouseValue = int((mouseX / self.width()) * (self._maximum - self._minimum) + self._minimum)

            if self._lastMouseValue >= self._lowValue - 1 and self._lastMouseValue < self._lowValue + 1:
                self.setLowValue(mouseValue)
            elif self._lastMouseValue >= self._highValue -1 and self._lastMouseValue < self._highValue + 1:
                self.setHighValue(mouseValue)
            elif self._lastMouseValue < self._highValue and self._lastMouseValue > self._lowValue:
                deltaValue = (mouseValue - self._lastMouseValue)
                self.setLowValue(self._lowValue + deltaValue)
                self.setHighValue(self._highValue + deltaValue)

            self._lastMouseValue = mouseValue

    def paintEvent(self, paintEvent):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)

        # Draw background
        painter.setPen(QPen(QColorConstants.DarkGray, 0.8))
        painter.setBrush(QBrush(QColor(QColorConstants.LightGray)))
        painter.drawRoundedRect(self.PADDING, 
                                (self.height() - self.SLIDER_HEIGHT) / 2,
                                self.width() - 2 * self.PADDING,
                                self.SLIDER_HEIGHT,
                                2,
                                2)
        
        # Draw range
        painter.setBrush(QBrush(QColor(0x1E, 0x90, 0xFF)))
        painter.drawRect(self.PADDING + ((self.width() - 2 * self.PADDING) * (self._lowValue - self._minimum) / (self._maximum - self._minimum)),
                         (self.height() - self.SLIDER_HEIGHT) / 2,
                         (self.width() - 2 * self.PADDING) * (self._highValue - self._lowValue) / (self._maximum - self._minimum),
                         self.SLIDER_HEIGHT)
        
        # Draw lower handle
        painter.setBrush(QBrush(QColor(QColorConstants.White)))
        painter.drawRoundedRect(self.PADDING + ((self.width() - 2 * self.PADDING) * (self._lowValue - self._minimum) / (self._maximum - self._minimum)),
                                (self.height() - self.HANDLE_SIZE) / 2,
                                self.HANDLE_SIZE,
                                self.HANDLE_SIZE,
                                2,
                                2)
        
        # Draw higher handle
        painter.drawRoundedRect(self.PADDING + ((self.width() - 2 * self.PADDING) * (self._highValue - self._minimum) / (self._maximum - self._minimum)) - self.HANDLE_SIZE,
                                (self.height() - self.HANDLE_SIZE) / 2,
                                self.HANDLE_SIZE,
                                self.HANDLE_SIZE,
                                2,
                                2)
        
        painter.end()