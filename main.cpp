#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "MainWindow/MainWindow.h"
#include "Session/Session.h"
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // MainWindow* Game = new MainWindow(800, 800);
    // Game->setFixedSize(700, 700);
    // Game->showFullScreen();
    // Game->show();
    Session::GetInstance();
    Session::SetBoardDimension(10, 10);
    Session::SetMineNumber(10);

    Session::GetInstance().setupBoard();
    Session::GetInstance().serialize();
    Session::GetInstance().ResetInstance();
    Session::GetInstance().deserialize();
    return app.exec();
}