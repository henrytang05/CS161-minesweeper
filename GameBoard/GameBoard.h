#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include "../Square/Square.h"
class GameBoard;

class GameBoard : public QWidget {
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0) : QWidget(parent) {
        if (level == 1)
            BOARD_SIZE = 8;
        else if (level == 2)
            BOARD_SIZE = 10;
        else if (level == 3)
            BOARD_SIZE = 15;
        MINE_NUMBER = BOARD_SIZE * 3 / 4;
        setupGameBoard();
    }
    ~GameBoard() {}
   public slots:
    void squareClicked(Square* square, int row, int col);
    void restartClicked(GameBoard*);

   private:
    void initializeGameBoard();
    void setupGameBoard();
    bool isValidBombPosition(int row, int col);
    void updateSurroundingCells(int row, int col);
    void render_square(Square* square, int row, int col);
    void breakSurroundingCells(int row, int col);
    void revealAllBombs();
    void announcement(std::string);
    QGridLayout* mainGridLayout;

   public:
    inline static int BOARD_SIZE = 0;
    inline static int MINE_NUMBER = 0;
    inline static constexpr int CELL_SIZE = 50;

   private:
    std::vector<std::vector<Square*>> grid;
    std::vector<std::pair<int, int>> mines;
    QPushButton* replayButton;
};
#endif