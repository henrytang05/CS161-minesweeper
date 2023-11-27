#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QGridLayout>
#include <QWidget>
#include <random>
#include <vector>

// #include "../../../Memory/Memory.h"
#include "../../../Style/Style.h"
#include "../Square/Square.h"
class GameBoard : public QWidget {
    Q_OBJECT
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0) : QWidget(parent) {
        if (level == 1)
            BOARD_SIZE = 9;
        else if (level == 2)
            BOARD_SIZE = 16;
        else if (level == 3)
            BOARD_SIZE = 30;
        else
            BOARD_SIZE = 9;
        MINE_NUMBER = BOARD_SIZE * BOARD_SIZE / 4;
        setupGameBoard();
    }
    ~GameBoard() {}
    static void breakSurroundingCells(int row, int col);

   public:
    inline static int BOARD_SIZE = 8;
    inline static int MINE_NUMBER = 0;
    inline static int FLAG_NUMBER = MINE_NUMBER;
    static void revealAllBombs();
    void setupGameBoard();
    inline static std::vector<std::vector<Square*>> grid;

   private:
    void initializeGameBoard();
    bool isValidBombPosition(int row, int col);
    void updateSurrounding(int row, int col, char mode = 'm');

   signals:
    void result(bool);
};
#endif