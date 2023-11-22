#ifndef GAME_BOARD_PAGE_H
#define GAME_BOARD_PAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../../../Style/Style.h"
#include "../GameBoard/GameBoard.h"

class GameBoardPage : public QWidget {
   public:
    GameBoardPage(QWidget* parent = nullptr) : QWidget(parent) { setupGameBoardPage(); }
    ~GameBoardPage() { delete replayButton; }
    void setupGameBoardPage();
    GameBoard* Board;
    QPushButton* replayButton;
};

#endif