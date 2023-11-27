#include <QApplication>

#include "HomeWindow/HomeWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    HomeWindow* Game = new HomeWindow;
    Game->show();
    return app.exec();
}