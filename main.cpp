#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "MainWindow/MainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow* Game = new MainWindow(800, 800);
    Game->setFixSize(800, 800);

    return app.exec();
}