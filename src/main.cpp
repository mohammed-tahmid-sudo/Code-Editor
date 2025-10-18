#include <QApplication>
#include <QMenuBar>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qsciscintilla.h>
#include <cerrno>
#include <functional>
#include <qaction.h>
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
#include <unordered_map>

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

      static const std::unordered_map<std::string, std::function<QsciLexer *()>>
          lexers = {{".cpp", []() { return new QsciLexerCPP; }},
                    {".py", []() { return new QsciLexerPython; }},
                    {".java", []() { return new QsciLexerJava; }},
                    {".sql", []() { return new QsciLexerSQL; }},
                    {"MakeFile", []() { return new QsciLexerMakefile; }},
                    {"CMakeLists.txt", []() { return new QsciLexerCMake; }}};

      for (const auto &[ext, ctor] : lexers) {
        if (endsWith(path.toStdString(), ext)) {
          editor->setLexer(ctor());
        }
      }
    }

    QTextStream in(&file);
    editor->setText(in.readAll());
  }
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow window;

  QMenuBar *menubar = window.menuBar();
  QMenu *filemenu = menubar->addMenu("file");

  QAction *save = menubar->addAction("Save");

  QAction *save_as = menubar->addAction("Save as");

  QAction *open_folder = menubar->addAction("Open Folder");

  QAction *open_file = menubar->addAction("Open File");

  auto *editor = new QsciScintilla;
  auto *file_tree = new QTreeView;
  auto *model = new QFileSystemModel;

  editor->setMarginType(0, QsciScintilla::NumberMargin);
  editor->setMarginWidth(0, "0000"); // width for 4-digit line numbers
  editor->setMarginLineNumbers(0, true);

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
