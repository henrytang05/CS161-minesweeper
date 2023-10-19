#include "GameBoard/GameBoard.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    GameBoard chessApp;
    chessApp.show();
    return app.exec();
}
