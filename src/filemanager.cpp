// // Filemanager.cpp — part of the CodeEditor project
// #include <QApplication>
// #include <QMainWindow>
// #include <QMenuBar>
// #include <QFileDialog>
// #include <QMessageBox>
//
// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     QMainWindow window;
//
//     QMenuBar *menuBar = window.menuBar();
//     QMenu *fileMenu = menuBar->addMenu("File");
//
//     QAction *openAction = fileMenu->addAction("Open");
//
//     QObject::connect(openAction, &QAction::triggered, [&]() {
//         QString fileName = QFileDialog::getOpenFileName(&window, "Open File", "", "All Files (*)");
//         if (!fileName.isEmpty()) {
//             QMessageBox::information(&window, "Selected File", fileName);
//         }
//     });
//
//     window.show();
//     return app.exec();
// }
//
