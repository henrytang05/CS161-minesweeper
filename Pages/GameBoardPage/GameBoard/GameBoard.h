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
    Q_OBJECT
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0) : QWidget(parent) {
        if (level == 1)
            BOARD_SIZE = 8;
        else if (level == 2)
            BOARD_SIZE = 10;
        else if (level == 3)
            BOARD_SIZE = 15;
        else
            BOARD_SIZE = 8;
        MINE_NUMBER = BOARD_SIZE * BOARD_SIZE / 4;
        setupGameBoard();
    }
    ~GameBoard() {
        // delete replayButton;
        // for (auto& row : grid)
        //     for (auto& cell : row)
        //         if (cell != nullptr) delete cell;
        // delete mainGrid;
    }
    //    public slots:
    // void restartClicked(GameBoard*);
   public:
    static void breakSurroundingCells(int row, int col);

   private:
    void initializeGameBoard();
    bool isValidBombPosition(int row, int col);
    void updateSurroundingSquares(int row, int col);

   public:
    inline static int BOARD_SIZE = 0;
    inline static int MINE_NUMBER = 0;

    static void announcement(std::string);
    static void revealAllBombs();
    void setupGameBoard();

    inline static std::vector<std::vector<Square*>> grid;

    void render_square(int row, int col);
};
#endif