import sys
import subprocess
from PyQt5 import QtWidgets, QtCore
from ui_statistics import Ui_MainWindow  # Import the updated UI

class WorkerThread(QtCore.QThread):
    """Background thread to execute the C++ program without freezing UI."""
    result_ready = QtCore.pyqtSignal(str)  # Signal to send data back to the main thread

    def __init__(self, city):
        super().__init__()
        self.city = city

    def run(self):
        """Run the C++ program and emit the result."""
        try:
            result = subprocess.run(["./app", self.city], capture_output=True, text=True, check=True)
            self.result_ready.emit(result.stdout)  # Send output to main thread
        except Exception as e:
            self.result_ready.emit(f"Error: {e}")  # Send error to main thread

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # Connect button click
        self.ui.btn_generate.clicked.connect(self.run_statistics)

    def run_statistics(self):
        """Start the worker thread to process data without freezing UI."""
        selected_option = self.ui.combo_statistics.currentText()
        city = {
            "Lahore Statistics": "Lahore",
            "Peshawar Statistics": "Peshawar",
            "Combined Statistics": "Combined"
        }.get(selected_option, None)

        if not city:
            self.ui.text_display.setText("Invalid Selection")
            return

        # Disable button and show "Processing..." message
        self.ui.btn_generate.setEnabled(False)
        self.ui.text_display.setText("Processing... Please wait.")

        # Create and start worker thread
        self.worker = WorkerThread(city)
        self.worker.result_ready.connect(self.display_result)  # Connect signal to UI
        self.worker.start()

    def display_result(self, result):
        """Update the QTextEdit with the result once the worker finishes."""
        self.ui.text_display.setText(result)
        self.ui.btn_generate.setEnabled(True)  # Re-enable the button

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
