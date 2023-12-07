#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "MainWindow/MainWindow.h"
#include "Timer/Timer.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow* Game = new MainWindow(800, 800);
    Game->setFixedSize(700, 700);
    Game->showFullScreen();
    // Game->show();

    return app.exec();
}