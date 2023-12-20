#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "MainWindow/MainWindow.h"
#include "Session/Session.h"
#include "HomePage/HomePage.h"
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow* Game = new MainWindow;
    // Game->setFixedSize(700, 700);
    Game->showFullScreen();
    Game->show();
    QObject::connect(Game->homePage, &HomePage::exit, Game, &QCoreApplication::quit);

        return app.exec();
}