#include <QApplication>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qsciscintilla.h>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Create QScintilla editor
  QsciScintilla editor;

  // Set C++ lexer for syntax highlighting
  QsciLexerPython *lexer = new QsciLexerPython();
  editor.setLexer(lexer);

  // Enable line numbers in margin 1
  editor.setMarginType(1, QsciScintilla::NumberMargin);
  editor.setMarginLineNumbers(1, true);
  editor.setMarginWidth(1, 40);

  // UTF-8 support
  editor.setUtf8(true);


  // Resize and show
  editor.resize(800, 600);
  editor.show();

  return app.exec();
}
