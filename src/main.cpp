#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow w;
    QPlainTextEdit *editor = new QPlainTextEdit;
    w.setCentralWidget(editor);
    w.resize(800,600);
    w.show();
    return app.exec();
}
