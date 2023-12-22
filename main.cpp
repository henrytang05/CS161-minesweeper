#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "HomePage/HomePage.h"
#include "MainWindow/MainWindow.h"
#include "Session/Session.h"
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow* Game = new MainWindow;
    // Game->setFixedSize(900, 700);
    Game->showFullScreen();
    Game->show();
    Session::GetHighScores();
    QObject::connect(Game->homePage, &HomePage::exit, Game, &QCoreApplication::quit);

    int result = app.exec();
    delete Game;
    return result;
}