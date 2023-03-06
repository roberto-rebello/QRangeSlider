from QRangeSlider import QRangeSlider

from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QSpinBox, QPushButton

class MainWindow(QMainWindow):

    def __init__(self, parent = None):
        super().__init__(parent)

        self.setWindowTitle("QRangeSlider Demo - Python")
        self.setMinimumSize(500, 100)

        layout = QVBoxLayout()
        container = QWidget(self)
        container.setLayout(layout)
        self.setCentralWidget(container)

        minimum = QSpinBox()
        minimum.setRange(0, 200)
        maximum = QSpinBox()
        maximum.setRange(0, 200)
        lowValue = QSpinBox()
        lowValue.setRange(0, 100)
        highValue = QSpinBox()
        highValue.setRange(0, 100)

        valuesLayout = QHBoxLayout()
        valuesLayout.addWidget(minimum)
        valuesLayout.addWidget(lowValue)
        valuesLayout.addWidget(highValue)
        valuesLayout.addWidget(maximum)
        layout.addLayout(valuesLayout)

        qRangeSlider = QRangeSlider()
        qRangeSlider.setRange(0, 100)
        qRangeSlider.setLowValue(10)
        qRangeSlider.setHighValue(90)
        layout.addWidget(qRangeSlider)

        minimum.setValue(qRangeSlider.minimum())
        lowValue.setValue(qRangeSlider.lowValue())
        highValue.setValue(qRangeSlider.highValue())
        maximum.setValue(qRangeSlider.maximum())

        # QRangeSlider values
        minimum.valueChanged.connect(qRangeSlider.setMinimum)
        lowValue.valueChanged.connect(qRangeSlider.setLowValue)
        highValue.valueChanged.connect(qRangeSlider.setHighValue)
        maximum.valueChanged.connect(qRangeSlider.setMaximum)

        # QRangeSlider update signals
        qRangeSlider.minimumChange.connect(minimum.setValue)
        qRangeSlider.lowValueChange.connect(lowValue.setValue)
        qRangeSlider.highValueChange.connect(highValue.setValue)
        qRangeSlider.maximumChange.connect(maximum.setValue)

        qRangeSlider.rangeChange.connect(lowValue.setRange)
        qRangeSlider.rangeChange.connect(highValue.setRange)

        reset = QPushButton("Reset")
        layout.addWidget(reset)
        reset.clicked.connect(lambda state: qRangeSlider.setRange(0, 100))
        reset.clicked.connect(lambda state: lowValue.setValue(10))
        reset.clicked.connect(lambda state: highValue.setValue(90))