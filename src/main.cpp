#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <qmenu.h>
#include <qmenubar.h>
#include <qnamespace.h>
#include <qtextedit.h>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow window;

  QTextEdit *edit = new QTextEdit();

  edit->setPlaceholderText("Type someting damn it!!!!!");

  QMenuBar *menubar = new QMenuBar();
  QMenu *file = menubar->addMenu("FILE");
  
  file->addAction("Save");

  window.setMenuBar(menubar);
  window.setCentralWidget(edit);
  window.resize(1100, 800);
  window.show();

  return app.exec();
}
