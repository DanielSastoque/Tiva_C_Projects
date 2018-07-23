import sys
import atexit
import subprocess

from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QFileDialog
from PySide2.QtCore import QFile, QObject

import os
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

UI_FILE = 'mainwindow.ui'
DEFAULT_PROJ = "/Blink"

class Application(QObject):

    def __init__(self, ui_file, parent=None):
        super(Application, self).__init__(parent)
        ui_file = QFile(ui_file)
        ui_file.open(QFile.ReadOnly)

        loader = QUiLoader()
        self.window = loader.load(ui_file)

        self.jtag = False                   # OpenOCD connection is running?
        atexit.register(self.kill_openocd)  # Kill OpenOCD at exit

        self.window.make.clicked.connect(lambda x: self.make(""))
        self.window.clean.clicked.connect(lambda x: self.make("clean"))
        self.window.flash.clicked.connect(lambda x: self.make("flash"))
        self.window.debug.clicked.connect(self.debug)

        self.window.project.clicked.connect(self.select_project)
        self.selected_project = BASE_DIR + DEFAULT_PROJ

        self.window.show()

    def make(self, flag):
        self.kill_openocd()
        
        command = "cd {} && make {}".format(self.selected_project, flag)
        subprocess.call(['/bin/bash', '-i', '-c', command])

    def debug(self):
        self.kill_openocd()
        command = "cd {} && make openocd".format(self.selected_project)
        self.openocd = subprocess.Popen(['/bin/bash', '-i', '-c', command])

        self.make("gdb")
        self.jtag = True

    def kill_openocd(self):
        if self.jtag:
            self.jtag = False
            self.openocd.terminate()

    def select_project(self):
        file_path = QFileDialog.getOpenFileName(self.window.centralwidget,
                                                "Open Image", BASE_DIR,
                                                "makefile")[0].replace("makefile", "")
        file_name = file_path.split("/")[-2]
        self.selected_project = file_path
        self.window.selected_project.setText(file_name)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = Application(UI_FILE)
    sys.exit(app.exec_())
