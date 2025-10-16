#include <QApplication>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qsciscintilla.h>
#include <cerrno>
#include <qapplication.h>
#include <qdir.h>
#include <qfilesystemmodel.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qsplitter.h>
#include <qtreeview.h>
#include <qwindowdefs.h>
#include <string>

bool endsWith(const std::string &str, const std::string &suffix) {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
void openFileFromTree(const QModelIndex &index, QFileSystemModel *model,
                      QsciScintilla *editor) {
  QString path = model->filePath(index);
  QFileInfo info(path);
  if (info.isFile()) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

      if (endsWith(path.toStdString(), ".cpp")) {

        auto *lexer = new QsciLexerCPP;
        editor->setLexer(lexer);

      } else if (endsWith(path.toStdString(), ".py")) {

        auto *lexer = new QsciLexerPython;
        editor->setLexer(lexer);

      } else if (endsWith(path.toStdString(), ".java")) {

        auto *lexer = new QsciLexerJava;
        editor->setLexer(lexer);

      } else if (endsWith(path.toStdString(), ".sql")) {

        auto *lexer = new QsciLexerSQL;
        editor->setLexer(lexer);

      } else if (endsWith(path.toStdString(), "MakeFile")) {

        auto *lexer = new QsciLexerMakefile;
        editor->setLexer(lexer);

      } else if (endsWith(path.toStdString(), "CmakeLists.txt")) {

        auto *lexer = new QsciLexerCMake;
        editor->setLexer(lexer);
      }

      QTextStream in(&file);
      editor->setText(in.readAll());
    }
  }
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow window;

  QMenuBar *menubar = new QMenuBar(&window);

  auto *editor = new QsciScintilla;
  auto *file_tree = new QTreeView;
  auto *model = new QFileSystemModel;
  auto *lexer = new QsciLexerCPP;

  editor->setLexer(lexer);
  model->setRootPath(QDir::currentPath());
  model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

  file_tree->setModel(model);

  file_tree->setRootIndex(model->index(QDir::currentPath()));
  file_tree->setHeaderHidden(true);

  auto *splitter = new QSplitter(Qt::Horizontal);

  splitter->addWidget(file_tree);
  splitter->addWidget(editor);
  splitter->setStretchFactor(1, 1);

  QObject::connect(file_tree, &QTreeView::clicked,
                   [&](const QModelIndex &index) {
                     openFileFromTree(index, model, editor);
                   });

  window.setCentralWidget(splitter);

  window.setWindowTitle("Code Editor");

  window.resize(1200, 900);
  window.show();
  return app.exec();
}
