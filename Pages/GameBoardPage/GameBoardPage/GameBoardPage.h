#ifndef GAME_BOARD_PAGE_H
#define GAME_BOARD_PAGE_H

#include "../../../Style/Style.h"
#include "../GameBoard/GameBoard.h"

class GameBoardPage : public QWidget {
   public:
    GameBoardPage(QWidget* parent = nullptr) : QWidget(parent) {
        Board = new ("Game Board") GameBoard();
        setupGameBoardPage();
    }
    ~GameBoardPage() {
        delete replayButton;
        delete Board;
    }
    void setupGameBoardPage();
    GameBoard* Board;
    QPushButton* replayButton;
};

#endif