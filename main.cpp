#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "HomePage/HomePage.h"
#include "MainWindow/MainWindow.h"
#include "Session/Session.h"
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow* Game = new MainWindow;
    Game->showFullScreen();
    Game->show();
    Session::GetHighScores();

    int result = app.exec();
    delete Game;
    return result;
}
