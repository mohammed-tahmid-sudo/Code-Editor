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
#include <qaction.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtextedit.h>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow window;

  QTextEdit *edit = new QTextEdit();

  edit->setPlaceholderText("Type someting damn it!!!!!");

  QMenuBar *menubar = new QMenuBar();
  QMenu *file = menubar->addMenu("FILE");

  QAction *save = file->addAction("Save");

  QAction *something = file->addAction("New");

  QObject::connect(save, &QAction::triggered, [&]() {

    QString path = QFileDialog::getSaveFileName(

        &window, "Save File", "", "Text Files (*.txt);;All Files (*)");

    if (!path.isEmpty()) {
      QFile file(path);
      if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << edit->toPlainText();

      }
    }
  });

  window.setMenuBar(menubar);
  window.setCentralWidget(edit);
  window.resize(1100, 800);
  window.show();

  return app.exec();
}
