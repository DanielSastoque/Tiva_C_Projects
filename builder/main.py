import sys
import subprocess

from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication
from PySide2.QtCore import QFile, QObject

UI_FILE = 'mainwindow.ui'
C_PROJ = "../Blink"

class Application(QObject):

    def __init__(self, ui_file, parent=None):
        super(Application, self).__init__(parent)
        ui_file = QFile(ui_file)
        ui_file.open(QFile.ReadOnly)

        loader = QUiLoader()
        self.window = loader.load(ui_file)

        self.window.make.clicked.connect(lambda x: self.make(""))
        self.window.clean.clicked.connect(lambda x: self.make("clean"))
        self.window.flash.clicked.connect(lambda x: self.make("flash"))
        self.window.debug.clicked.connect(self.debug)

        self.window.show()

    def make(self, flag):
        command = "cd {} && make {}".format(C_PROJ, flag)
        subprocess.call(['/bin/bash', '-i', '-c', command])

    def debug(self):
        command = "cd {} && make openocd".format(C_PROJ)
        subprocess.Popen(['/bin/bash', '-i', '-c', command])

        self.make("gdb")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    form = Application(UI_FILE)
    sys.exit(app.exec_())
