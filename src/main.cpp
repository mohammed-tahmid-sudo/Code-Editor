#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <qaction.h>
#include <qglobal.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtextedit.h>
#include <thread>

void autosave(QString path, QTextEdit *edit) {
  while (true) {
    std::cout << "the loop is running " << std::endl;
    if (!path.isEmpty()) {
      QFile file(path);
      if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << edit->toPlainText();
        std::cout << "file saved" << std::endl;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  bool saved = false;
  QString path;

  QApplication app(argc, argv);

  QMainWindow window;

  QTextEdit *edit = new QTextEdit();

  edit->setPlaceholderText("Type someting damn it!!!!!");

  QMenuBar *menubar = new QMenuBar();
  QMenu *file = menubar->addMenu("FILE");

  QAction *save = file->addAction("Save");

  QAction *something = file->addAction("New");

  QObject::connect(save, &QAction::triggered, [&]() {
    path = QFileDialog::getSaveFileName(

        &window, "Save File",
        ""
        "",
        "Text Files (*.txt);;Python file (*.py);;C (*.c);;All Files (*)");

    if (!path.isEmpty()) {
      QFile file(path);
      if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << edit->toPlainText();
        saved = true;
      }
    }
  });

  if (saved) {
    std::thread tl(autosave, path, edit);
    tl.join();
  }

  window.setMenuBar(menubar);
  window.setCentralWidget(edit);
  window.resize(1100, 800);
  window.show();

  return app.exec();
}
