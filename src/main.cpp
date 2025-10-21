#include <QApplication>
#include <QFileDialog>
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
#include <functional>
#include <iostream>
#include <qaction.h>
#include <qapplication.h>
#include <qdebug.h>
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

// Helper function to check if a string ends with a given suffix
bool endsWith(const std::string &str, const std::string &suffix) {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// Functions called by menu actions
// void save_file(QMainWindow window, QsciScintilla *editor) {
//   QString fileName = QFileDialog::getSaveFileName(
//       &window, "Save File", "", "C++ Files (*.cpp);;All Files (*)");
//   if (!fileName.isEmpty()) {
//     QFile file(fileName);
//     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//       QTextStream out(&file);
//       out << editor->text(); // save editor content
//       file.close();
//     }
//   }
// }

void save_file(QMainWindow *window, QsciScintilla *editor) {
  QString fileName = QFileDialog::getSaveFileName(
      window, "Save File", "", "C++ Files (*.cpp);;All Files (*)");

  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << editor->text();
    }
  }
}

void save_file_as() { std::cout << "FILE Save as  PRESSED" << std::endl; }
void open_folder_func() { std::cout << "Folder SAVE PRESSED" << std::endl; }
void open_file_func() { std::cout << "Folder SAVE AS PRESSED" << std::endl; }

// Function to open a file from the file tree and set the appropriate lexer
void openFileFromTree(const QModelIndex &index, QFileSystemModel *model,
                      QsciScintilla *editor) {
  QString path = model->filePath(index); // Get full path from tree index
  QFileInfo info(path);

  if (info.isFile()) { // Only process files
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

      // Map file extensions to corresponding QScintilla lexers
      static const std::unordered_map<std::string, std::function<QsciLexer *()>>
          lexers = {{".cpp", []() { return new QsciLexerCPP; }},
                    {".py", []() { return new QsciLexerPython; }},
                    {".java", []() { return new QsciLexerJava; }},
                    {".sql", []() { return new QsciLexerSQL; }},
                    {"MakeFile", []() { return new QsciLexerMakefile; }},
                    {"CMakeLists.txt", []() { return new QsciLexerCMake; }}};

      // Set lexer based on file extension
      for (const auto &[ext, ctor] : lexers) {
        if (endsWith(path.toStdString(), ext)) {
          editor->setLexer(ctor());
        }
      }
    }

    // Read the file content and set it to the editor
    QTextStream in(&file);
    editor->setText(in.readAll());
  }
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv); // Qt application
  QMainWindow window;           // Main window

  // Menu bar setup
  QMenuBar *menubar = window.menuBar();
  QMenu *filemenu = menubar->addMenu("file");

  // File menu actions
  // QAction *save = filemenu->addAction("Save");
  // QObject::connect(save, &QAction::triggered, []() { save_file(window, editor
  // ); });
  //
  // QAction *save_as = filemenu->addAction("Save as");
  // QObject::connect(save_as, &QAction::triggered, []() { save_file_as(); });
  //
  // QAction *open_folder = filemenu->addAction("Open Folder");
  // QObject::connect(open_folder, &QAction::triggered,
  //                  []() { open_folder_func(); });
  //
  // QAction *open_file = filemenu->addAction("Open File");
  // QObject::connect(open_file, &QAction::triggered, []() { open_file_func();
  // });

  // Editor and file tree setup
  auto *editor = new QsciScintilla;   // Code editor widget
  auto *file_tree = new QTreeView;    // File explorer widget
  auto *model = new QFileSystemModel; // File system model

  // File menu actions
  QAction *save = filemenu->addAction("Save");
  QObject::connect(save, &QAction::triggered,
                   [&window, &editor]() { save_file(&window, editor); });

  QAction *save_as = filemenu->addAction("Save as");
  QObject::connect(save_as, &QAction::triggered, []() { save_file_as(); });

  QAction *open_folder = filemenu->addAction("Open Folder");
  QObject::connect(open_folder, &QAction::triggered,
                   []() { open_folder_func(); });

  QAction *open_file = filemenu->addAction("Open File");
  QObject::connect(open_file, &QAction::triggered, []() { open_file_func(); });

  // Configure editor line numbers
  editor->setMarginType(0, QsciScintilla::NumberMargin);
  editor->setMarginWidth(0, "0000"); // width for 4-digit line numbers
  editor->setMarginLineNumbers(0, true);

  // Configure file tree model
  model->setRootPath(QDir::currentPath());
  model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  file_tree->setModel(model);
  file_tree->setRootIndex(model->index(QDir::currentPath()));
  file_tree->setHeaderHidden(true);

  // Splitter to show file tree and editor side by side
  auto *splitter = new QSplitter(Qt::Horizontal);
  splitter->addWidget(file_tree);
  splitter->addWidget(editor);
  splitter->setStretchFactor(1, 1); // Give editor more space

  // Connect file tree click to opening file
  QObject::connect(file_tree, &QTreeView::clicked,
                   [&](const QModelIndex &index) {
                     openFileFromTree(index, model, editor);
                   });

  window.setCentralWidget(splitter); // Set splitter as main content

  window.setWindowTitle("Code Editor"); // Window title
  window.resize(1200, 900);             // Initial size
  window.show();                        // Show window

  return app.exec(); // Start Qt event loop
}
