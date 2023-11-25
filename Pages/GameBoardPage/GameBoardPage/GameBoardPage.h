#ifndef GAME_BOARD_PAGE_H
#define GAME_BOARD_PAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <string>

#include "../../../Style/Style.h"
#include "../GameBoard/GameBoard.h"

class GameBoardPage : public QWidget {
    Q_OBJECT
   public:
    GameBoardPage(QStackedWidget* parent = nullptr, int level = 0) : QWidget(parent) {
        Board = new ("Game Board") GameBoard(this, level);
        replayButton = new ("Replay Button") QPushButton("Replay", this);
        styleButton(replayButton, "12D9C4", true);
        setupGameBoardPage();
    }
    ~GameBoardPage() { delete replayButton; }

    void setupGameBoardPage();

   public:
    GameBoard* Board;
    QPushButton* replayButton;
};

#endif