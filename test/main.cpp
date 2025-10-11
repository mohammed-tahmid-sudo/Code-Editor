#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QTextStream>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        QMenu *fileMenu = menuBar()->addMenu("File");
        QAction *saveAction = fileMenu->addAction("Save");
        connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    }

private:
    void saveFile() {
        QString path = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
        if (!path.isEmpty()) {
            QFile file(path);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << "Your content here";
            }
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

