import sys
from PySide6.QtWidgets import QApplication, QMainWindow

app = QApplication(sys.argv)

window = QMainWindow()

window.setWindowTitle("hello world")
window.setGeometry(100, 100, 800, 600)  # x, y, width, height
window.show()
sys.exit(app.exec())
