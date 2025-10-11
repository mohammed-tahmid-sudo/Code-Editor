#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;

    // Sidebar
    QWidget *sidebar = new QWidget;
    sidebar->setFixedWidth(150); // initial width
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->addWidget(new QPushButton("Button 1"));
    sidebarLayout->addWidget(new QPushButton("Button 2"));
    sidebarLayout->addStretch();

    // Main content
    QWidget *mainContent = new QWidget;
    mainContent->setStyleSheet("background-color: lightgray;");

    // Toggle button
    QPushButton *toggleButton = new QPushButton("Toggle Sidebar");

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(&window);
    layout->addWidget(sidebar);
    layout->addWidget(mainContent, 1);

    // Toggle action
    QObject::connect(toggleButton, &QPushButton::clicked, [&]() {
        if (sidebar->isVisible())
            sidebar->hide();
        else
            sidebar->show();
    });

    // Add toggle button somewhere (top of main content)
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContent);
    mainLayout->addWidget(toggleButton);
    mainLayout->addStretch();

    window.show();
    return app.exec();
}

