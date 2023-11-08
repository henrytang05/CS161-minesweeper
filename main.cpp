#include "GameBoard/GameBoard.h"
#include "HomeWindow/HomeWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    HomeWindow* home = new HomeWindow();
    home->show();
    return app.exec();
}
