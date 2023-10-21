#include "GameBoard/GameBoard.h"
#include "HomeWindow/HomeWindow.h"
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    GameBoard game;
    return app.exec();
}
