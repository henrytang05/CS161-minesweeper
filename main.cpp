#include <QApplication>

#include "MainWindow/MainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow* Game = new MainWindow;
    Game->show();
    return app.exec();
}