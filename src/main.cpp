#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;
    auto *editor = new QTextEdit;
    window.setCentralWidget(editor);
    window.resize(800, 600);
    window.show();
    return app.exec();
}

