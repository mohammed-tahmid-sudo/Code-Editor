#include <QApplication>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qsciscintilla.h>
#include <qapplication.h>
#include <qdir.h>
#include <qfilesystemmodel.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qsplitter.h>
#include <qtreeview.h>
#include <qwindowdefs.h>
void openFileFromTree(const QModelIndex &index, QFileSystemModel *model,
                      QsciScintilla *editor) {
  QString path = model->filePath(index);
  QFileInfo info(path);
  if (info.isFile()) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QTextStream in(&file);
      editor->setText(in.readAll());
    }
  }
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow window;

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
