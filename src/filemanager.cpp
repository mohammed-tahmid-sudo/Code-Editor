// #include "SaveWindow.h"
// #include <QMenuBar>
// #include <QFileDialog>
// #include <QTextStream>
// #include <QAction>
//
// SaveWindow::SaveWindow() {
//     setWindowTitle("Save Menu");
//
//     edit = new QTextEdit(this);
//     setCentralWidget(edit);
//
//     QMenu *fileMenu = menuBar()->addMenu("File");
//     QAction *saveAction = fileMenu->addAction("Save");
//
//     connect(saveAction, &QAction::triggered, this, &SaveWindow::saveFile);
// }
//
// void SaveWindow::saveFile() {
//     QString path = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
//     if (!path.isEmpty()) {
//         QFile file(path);
//         if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//             QTextStream out(&file);
//             out << edit->toPlainText();
//         }
//     }
// }
//
