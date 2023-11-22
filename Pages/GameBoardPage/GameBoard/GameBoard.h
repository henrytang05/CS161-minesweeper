#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <random>
#include <vector>
#include "../../../Memory/Memory.h"
#include "../../../Style/Style.h"
#include "../Square/Square.h"

class GameBoard : public QWidget {
    friend class Square;

   public:
    GameBoard(int level = 0, QWidget* parent = nullptr) : QWidget(parent) {
        if (level == 1)
            BOARD_SIZE = 8;
        else if (level == 2)
            BOARD_SIZE = 10;
        else if (level == 3)
            BOARD_SIZE = 15;
        Square::MINE_NUMBER = BOARD_SIZE * BOARD_SIZE / 4;
        setupGameBoard();
    }
    ~GameBoard() {
        // delete replayButton;
        // for (auto& row : grid)
        //     for (auto& cell : row)
        //         if (cell != nullptr) delete cell;
        // delete mainGrid;
    }
   public slots:
    void restartClicked(GameBoard*);

   private:
    void initializeGameBoard();
    bool isValidBombPosition(int row, int col);
    void updateSurroundingCells(int row, int col);
    static void breakSurroundingCells(int row, int col);

   public:
    inline static int BOARD_SIZE = 0;
    static void announcement(std::string);
    static void revealAllBombs();
    void setupGameBoard();

    QWidget* mainGrid = new ("main grid") QWidget(this);
    QPushButton* replayButton;
    inline static std::vector<std::vector<Square*>> grid;
};
#endif