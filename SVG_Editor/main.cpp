#include <QApplication>

#include <QSettings>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("SVG Editor");
    QApplication::setOrganizationName("CourseProject");

    MainWindow window;
    window.show();

    return app.exec();
}
